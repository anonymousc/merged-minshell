#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtins.h"

#define MAX_COMMAND_LENGTH 1024

void execute_command(t_execution *exec, t_env *env) 
{
    exec->av = (char **)malloc(sizeof(char *) * 3);//ft_count_word instead of 3
    exec->av = ft_split(exec->input, ' '); 
    // printf("data == %s\n" , exec->av[1]);
    // exit(1);
    // if (strcmp(spl[0], "cd") == 0)
    // {
    //     my_cd(exec);
    // }
    if (strncmp(exec->av[0], "export", 7) == 0)
        my_export(exec);
    if(!strncmp(exec->av[0] , "env" , 4))
        my_env(env);
}

int main(int ac, char **av, char **env)
{
    char *input;
    char prompt[] = "MyShell$ ";

    printf("Welcome to MyShell. Type 'exit' or 'quit' to exit.\n");

    t_execution *exec;

    exec = malloc(sizeof(t_execution));
    exec->ac = ac;
    exec->env_orginal = env;

    t_env *envi = make_env(exec);
    // exec->env = envi;

    while (1) 
    {
        exec->input = readline(prompt);

        if (exec->input == NULL) 
        {
            printf("\nExiting shell...\n");
            break;
        }

        if (strlen(exec->input) > 0) 
        {
            add_history(exec->input);

            if (strcmp(exec->input, "exit") == 0 || strcmp(exec->input, "quit") == 0) 
            {
                printf("Exiting shell...\n");
                free(exec->input);
                break;
            }

            execute_command(exec, envi);
        }

        free(exec->input);
    }

    return 0;
}
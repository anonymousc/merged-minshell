#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtins.h"

#define MAX_COMMAND_LENGTH 1024

int main(int ac, char **av, char **env)
{
    (void) ac;
    (void) av;

    // char *input;
    char prompt[] = "MyShell$ ";

    printf("Welcome to MyShell. Type 'exit' or 'quit' to exit.\n");

    t_execution *exec;

    exec = malloc(sizeof(t_execution));
    exec->ac =count_words(exec->input, ' ');
    exec->env_orginal = env;
    exec->av = (char **)malloc(sizeof(char *) * exec->ac);
    exec->av = ft_split(exec->input, ' '); 

    t_env *envi = make_env(exec);
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

            execute_builtins(exec);
        }

        free(exec->input);
    }

    return 0;
}
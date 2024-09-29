#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"

int find_pipe_index(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        if (strcmp(av[i], "|") == 0)
        {
            return i;
        }
    }
    return -1;
}

char *find_path(char *cmd, char **env)
{
    char *full_path;
    char *full_command;
    char *path_var = NULL;
    
    int j = 0;
    
    if (strchr(cmd , '/') && access (cmd, F_OK | X_OK))
        return NULL;
    while (env[j])
    {
        if (strncmp(env[j], "PATH=", 5) == 0)
        {
            path_var = env[j] + 5;
            break;
        }
        j++;
    }

    if (!path_var)
        return NULL;

    char **paths = ft_split(path_var, ':');
    if (!paths)
        return NULL;

    int i = 0;
    while (paths[i])
    {
        if (strstr(cmd, paths[i]))
        {
            if (!access(cmd, F_OK | X_OK))
                return cmd;
            return NULL;
        }
        full_path = ft_strjoin(paths[i], "/");
        full_command = ft_strjoin(full_path, cmd);
        
        free(full_path);

        if (access(full_command, F_OK | X_OK) == 0)
        {
            return full_command;
        }
        free(full_command);
        i++;    
    }
    return NULL;
}


void pipe_and_execute(char **cmd1, char **cmd2, char **env)
{
    int fd[2];
    pid_t id1, id2;
    // int status;
    
    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    id1 = fork();
    if (id1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO); 
        close(fd[0]);               
        close(fd[1]);

        char *fullcmd1 = find_path(cmd1[0], env);

        execve(fullcmd1, cmd1, env);
        perror ("cant execute cmd1");
        exit(EXIT_FAILURE);
    }

    id2 = fork();
    if (id2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);   
        close(fd[1]);       
        close(fd[0]);

        char *fullcmd2 = find_path(cmd2[0], env);

        execve(fullcmd2, cmd2, env);
        perror ("cant execute cmd2");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(id1, NULL, 0);
    waitpid(id2, NULL, 0);
}

int main(int ac, char *av[], char **env)
{
    int pipe_index = find_pipe_index(ac, av);
    
    av[pipe_index] = NULL;
    char **cmd1 = &av[1];
    char **cmd2 = &av[pipe_index + 1];

    pipe_and_execute(cmd1, cmd2, env);

    return 0;
}
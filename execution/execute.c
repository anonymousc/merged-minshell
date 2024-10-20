// #include "builtins.h"
#include "../includes/minishell.h"

// int execute_builtins(t_exec *exec)
// {
// 	int ret;
// 	if (strncmp(exec->av[0], "echo", 5) == 0)
// 		ret = my_echo(exec->ac, exec->av);
// 	else if (strncmp (exec->av[0], "cd", 3) == 0)
// 		ret = my_cd(exec);
// 	else if (strncmp (exec->av[0], "pwd", 4) == 0)
// 		ret = my_pwd();
// 	else if (strncmp (exec->av[0] , "env", 4) == 0)
// 		ret = my_env(exec->env);
// 	else if (strncmp(exec->av[0] , "export", 7) == 0)
// 		ret = my_export(exec);
// 	else 
// 		return 1;
// }

char *find_path(char *cmd, char **env)
{
    char *full_path;
    char *full_command;
    char *path_var = NULL;
    
    int j = 0;
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
        full_path = ft_strjoin(paths[i], "/");
        full_command = ft_strjoin(full_path, cmd);
        
        free(full_path);

        if (access(full_command, F_OK) == 0)
        {
            return full_command;
        }
        free(full_command);
        i++;    
		}
    return NULL;
}

void redirect_io(t_execution **exec)
{
    if ((*exec)->fd_out != 1)
    {
        dup2((*exec)->fd_out, STDOUT_FILENO);
        close((*exec)->fd_out);
    }
    else if ((*exec)->fd_append != 0)
    {
        dup2((*exec)->fd_append, STDOUT_FILENO);
        close((*exec)->fd_append);
    }

    if ((*exec)->fd_in != 0)
    {
        dup2((*exec)->fd_in, STDIN_FILENO);
        close((*exec)->fd_in);
    }
    else if ((*exec)->fd_heredoc != 0)
    {
        dup2((*exec)->fd_heredoc, STDIN_FILENO);
        close((*exec)->fd_heredoc);
    }
}

// void execute_bins(t_execution **exec, char **env)
// {
//     t_execution *curr = *exec;
//     int status;
//     pid_t pid;
//     int cmd_count = 0;
// 	int i = 0;
//     int prev_pipe[2] = {0, 1};
//     int curr_pipe[2];

//     t_execution *temp = curr;
//     while (temp && temp->next)
//     {
//         cmd_count++;
//         temp = temp->next;
//     }

//     while (curr != NULL)
//     {
//         if (i < cmd_count - 1)
//         {
//             if (pipe(curr_pipe) == -1)
//             {
//                 perror("pipe");
//                 return;
//             }
//         }

//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             return;
//         }

//         if (pid == 0) 
//         {
//             if (i > 0)
//             {
//                 dup2(prev_pipe[0], STDIN_FILENO);
//                 close(prev_pipe[0]);
//                 close(prev_pipe[1]);
//             }

//             if (i < cmd_count - 1)
//             {
//                 close(curr_pipe[0]);
//                 dup2(curr_pipe[1], STDOUT_FILENO);
//                 close(curr_pipe[1]);
//             }
//             char *fullcmd = find_path(curr->cmd[0], env);
//             if (!fullcmd)
//             {
//                 exit(1);
//             }

// 			redirect_io(&curr);

//             if (execve(fullcmd, curr->cmd, env) == -1)
//             {
//                 perror("execve");
//                 free(fullcmd);
//                 exit(1);
//             }

//         }
//         else 
//         {
//             if (i > 0)
//             {
//                 close(prev_pipe[0]);
//                 close(prev_pipe[1]);
//             }

//             if (i < cmd_count - 1)
//             {
//                 prev_pipe[0] = curr_pipe[0];
//                 prev_pipe[1] = curr_pipe[1];
//             }
//         }
// 		i++;
// 		curr = curr->next;
//     }

//     while (wait(&status) > 0);
// }

void	free_stack1(t_execution **stack)
{
	t_execution	*tmp;

	tmp = *stack;
	while (tmp)
	{
		*stack = (*stack)->next;
		free(tmp);
		tmp = *stack;
	}
	stack = NULL;
}

void execute_bins(t_execution **exec, char **env)
{
    t_execution *curr = *exec;
    int status;
    pid_t *pids;
    int cmd_count = 0;
    int i = 0;
    int prev_pipe[2] = {0, 1};
    int curr_pipe[2];

    t_execution *temp = curr;
    while (temp)
    {
        cmd_count++;
        temp = temp->next;
    }
    pids = malloc(sizeof(pid_t) * cmd_count);
    if (!pids)
        return;

    while (curr && i < cmd_count)
    {
        if (i < cmd_count - 1)
        {
            if (pipe(curr_pipe) == -1)
            {
                perror("pipe");
                free(pids);
                return;
            }
        }

        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
            free(pids);
            return;
        }

        if (pids[i] == 0)
        {
            if (i > 0)
            {
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }

            if (i < cmd_count - 1)
            {
                close(curr_pipe[0]);
                dup2(curr_pipe[1], STDOUT_FILENO);
                close(curr_pipe[1]);
            }

            redirect_io(&curr);

            char *fullcmd = find_path(curr->cmd[0], env);
            if (!fullcmd)
            {
                fprintf(stderr, "Command not found: %s\n", curr->cmd[0]);
                free_stack1(&curr);
                free(pids);
                exit(1);
            }

            if (execve(fullcmd, curr->cmd, env) == -1)
            {
                free_stack1(&curr);
                perror("execve");
                free(fullcmd);
                free(pids);
                exit(1);
            }
        }
        else
        {
            if (i > 0)
            {
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }

            if (i < cmd_count - 1)
            {
                prev_pipe[0] = curr_pipe[0];
                prev_pipe[1] = curr_pipe[1];
            }
        }

        curr = curr->next;
        i++;
    }

        for (i = 0; i < cmd_count; i++)
        {
            waitpid(pids[i], &status, 0);
        }
        free(pids);
}
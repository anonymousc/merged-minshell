#include "../includes/minishell.h"


void printenv(char **s)
{
	int i = 0;
	while (s[i])
	{
		printf ("env == %s\n", s[i]);
		i++;
	}
}

int execute_builtins(t_execution *exec)
{
	int ret = 0;
	// if (strncmp(exec->cmd[0], "echo", 5) == 0)
    // {
	// 	ret = my_echo(exec->cmd);
    // }
	// if (strncmp (exec->cmd[0], "cd", 3) == 0)
	// 	ret = my_cd(exec);
	if (strncmp(exec->cmd[0], "pwd", 4) == 0)
    {
        printf("test\n");
		my_pwd();
        ret = 1;
    }
	// else if (strncmp (exec->av[0] , "env", 4) == 0)
	// 	ret = my_env(exec->env);
	// else if (strncmp(exec->av[0] , "export", 7) == 0)
	// 	ret = my_export(exec);
    return ret;
}

int check_builtins(t_execution *exec)
{
	int ret = 0;
	// if (strncmp(exec->cmd[0], "echo", 5) == 0)
    // {
	// 	ret = my_echo(exec->cmd);
    // }
	// if (strncmp (exec->cmd[0], "cd", 3) == 0)
	// 	ret = my_cd(exec);
	if (strncmp(exec->cmd[0], "pwd", 4) == 0)
    {
		ret = 1;
    }
	// else if (strncmp (exec->av[0] , "env", 4) == 0)
	// 	ret = my_env(exec->env);
	// else if (strncmp(exec->av[0] , "export", 7) == 0)
	// 	ret = my_export(exec);
    return ret;
}

void ft_free11(char **s)
{
    int i = 0;
    while(s[i++])
        free(s[i]);
    free(s);
}
char *find_path(char *cmd, char **env)
{
    char *full_path;
    char *full_command;
    char *path_var = NULL;
    if(!cmd)
        return NULL;
    if ((ft_strchr(cmd , '/') || ft_strchr(cmd , '.')))
    {
        if (!access(cmd , F_OK | X_OK))
            return cmd;
        else
            return NULL;
    }
    int j = 0;
    while (env && env[j])
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
    {
        free(paths);
        return NULL;
    }
    int i = 0;
    while (paths && paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_command = ft_strjoin(full_path, cmd);
        if (access(full_command, F_OK | X_OK) == 0)
        {
            return full_command;
        }
        free(full_command);
        i++;    
	}
    return NULL;
}


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

int redirect_io(t_execution **exec, int *flag)
{
    if ((*exec)->dflag == 1)
        return (printf("this is a directory\n"),-1);
    if((*exec)->fflag == 3)
        return (printf("ambigous redirection\n") , -1);
    if((*exec)->fflag == 2)
        return(printf("no such a file or directory\n"), -1);
    else if((*exec)->fd_out != 1)
    {
        if ((*exec)->fflag == 1)
            return (printf ("permission denied1\n"), -1);
        *flag = 1;
        dup2((*exec)->fd_out, STDOUT_FILENO);
        if ((*exec)->fd_out != STDOUT_FILENO) 
            close((*exec)->fd_out);
    }
    if ((*exec)->fd_append != 1)
    {
        if ((*exec)->fflag == 1)
            return (printf ("permission denied\n"), -1);
        dup2((*exec)->fd_append, STDOUT_FILENO);
        close((*exec)->fd_append);
    }

    if ((*exec)->fd_in != 0)
    {
        if((*exec)->fd_in == -1 || (*exec)->fflag == 1)
        {
            printf("no such a file or directory\n");
            return -1;
        }
        dup2((*exec)->fd_in, STDIN_FILENO);
        close((*exec)->fd_in);
    }
    else if ((*exec)->fd_heredoc != 0)
    {
        dup2((*exec)->fd_heredoc, STDIN_FILENO);
        close((*exec)->fd_heredoc);
    }
    return 0;
}
void sighhh(int data)
{
    (void)data;
    printf("\n");
}
void execute_bins(t_execution **exec, char **env)
{
    t_execution *curr = *exec;
    char *fullcmd;
    int status;
    pid_t *pids;
    int cmd_count = 0;
    int i = 0;
    int prev_pipe[2] = {0, 1};
    int curr_pipe[2];
    int flag = 0;
    int flag_s = 0;
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
        // flag_s = 0;
        // if(execute_builtins(curr))
        // {
        //     curr = curr->next;
        //     flag_s = 1;
        // }
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
            signal(SIGINT , sighhh);
            if (redirect_io(&curr, &flag) == -1)
            {
                free(pids);
                exit(1);
            }
            if (i > 0)
            {
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }

            if (i < cmd_count - 1)
            {
                close(curr_pipe[0]);
                if (flag == 0)
                    dup2(curr_pipe[1], STDOUT_FILENO);
                close(curr_pipe[1]);
            }
            if (curr->cmd[0] == NULL)
            {
                free_stack1(&curr);
                free(pids);
                exit(1);
            }
            fullcmd = find_path(curr->cmd[0], env);
            if (!fullcmd)
            {
                fprintf(stderr, "Command not found: %s\n", curr->cmd[0]);
                free_stack1(&curr);
                free(pids);
                exit(1);
            }
            if(!flag_s)
            {
                if (execve(fullcmd, curr->cmd, env) == -1)
                {
                    free_stack1(&curr);
                    perror("minishell");
                    free(fullcmd);
                    free(pids);
                    exit(1);
                }
            }
        }
        else
        {
            signal(SIGINT , SIG_IGN);
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
        if(curr)
            curr = curr->next;
        i++;
    }
        // int pid = 0;
        i = -1;
    
        while (++i < cmd_count)
            waitpid(pids[i] , &status , 0);
        if (WIFEXITED(status))
        {
            // int state = WEXITSTATUS(status);
        }
        free(pids);
}

// void execute_all (t_execution **exec, char **env)
// {
//     t_execution *curr = *exec;
    
// }
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

int execute_builtins(t_execution *exec  ,t_env **env, char **envs)
{
    (void) envs;
	int ret = 0;

     if(!*(exec->cmd))
            return (0);
	if (strncmp(exec->cmd[0], "echo", 5) == 0)
		ret = my_echo(exec->fds[0], exec->fds[2],  exec->cmd_len, exec->cmd);
	if (strncmp (exec->cmd[0], "cd", 3) == 0)
		ret = my_cd(exec , *env);
	if (strncmp(exec->cmd[0], "pwd", 4) == 0)
		ret = my_pwd(exec->fds[0], exec->fds[2], *env);
	else if (strncmp (exec->cmd[0] , "env", 4) == 0)
		ret = my_env(exec->fds[0],exec->fds[2], env);
	else if (strncmp(exec->cmd[0] , "export", 7) == 0)
        ret = my_export(exec , env, exec->fds[0], exec->fds[2]);
    else if (strncmp (exec->cmd[0] , "unset", 6) == 0)
        ret = my_unset(&exec, env);
    else if(!ft_strcmp(exec->cmd[0], "exit"))
        my_exit(exec);
    return ret;
}

int check_builtins(t_execution *exec)
{
	int ret;

    ret = 0;
     if(!exec->cmd[0])
         return (0);
	if (ft_strncmp(exec->cmd[0], "echo", 5) == 0)
		ret = 1;
	if (ft_strncmp(exec->cmd[0], "cd", 3) == 0)
		ret = 1;
	if (ft_strcmp(exec->cmd[0], "pwd") == 0)
		ret = 1;
	if (ft_strncmp(exec->cmd[0] , "export", 7) == 0)
        ret = 1;
	if (ft_strncmp (exec->cmd[0] , "env", 4) == 0)
		ret = 1;
    if (ft_strncmp (exec->cmd[0] , "unset", 6) == 0)
        ret = 1;
    if (ft_strcmp (exec->cmd[0] , "exit") == 0)
		ret = 1;
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
    char **paths = NULL;
    char *path_var = NULL;
    if(!cmd)
        return NULL;
    if ((ft_strchr(cmd , '/') || ft_strchr(cmd , '.')))
    {
        if (!access(cmd , F_OK ))
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
    if(ft_strchr(path_var , ':'))
    {
        paths = ft_split(path_var, ':');
        gc_add_double(MEMGRP_DEFAULT, (void **)paths, NULL);
    }
    else
    {
        paths = (char **)malloc(16);
        paths[0] = remove_quotes(path_var);
        paths[1] = NULL;

    }
    int i = 0;
    while (paths && paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        gc_add(0 , full_path, NULL);
        full_command = ft_strjoin(full_path, cmd);
        gc_add(0 , full_command, NULL);
        if (access(full_command, F_OK | X_OK) == 0)
            return (full_command);
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
		tmp = *stack;
		free(tmp);
	}
	stack = NULL;
}


int handle_output_redirection(t_execution **exec, int *flag)
{
    if ((*exec)->fds[0] != 1)
    {
        if ((*exec)->fds[4] == -1)
            return (printf("permission denied\n"), -1);
        *flag = 1;
        dup2((*exec)->fds[0], STDOUT_FILENO);
        if ((*exec)->fds[0] != STDOUT_FILENO)
            close((*exec)->fds[0]);
    }
    return 0;
}

int handle_append_redirection(t_execution **exec , int *flag)
{
    if ((*exec)->fds[2] != 1)
    {
        if ((*exec)->fds[4] == 1)
            return (printf("permission denied\n"), -1);
        *flag = 1;
        dup2((*exec)->fds[2], STDOUT_FILENO);
        close((*exec)->fds[2]);
    }
    return 0;
}

int handle_input_redirection(t_execution **exec)
{
    if ((*exec)->fds[1] != 0)
    {
        if ((*exec)->fds[1] == -1 || (*exec)->fds[4] == 1)
        {
            printf("no such a file or directory\n");
            return -1;
        }
        dup2((*exec)->fds[1], STDIN_FILENO);
        close((*exec)->fds[1]);
    }
    return 0;
}

int handle_heredoc_redirection(t_execution **exec)
{
    if ((*exec)->fds[3] != 0)
    {
        dup2((*exec)->fds[3], STDIN_FILENO);
        close((*exec)->fds[3]);
    }
    return 0;
}

int redirect_io(t_execution **exec, int *flag)
{
    if ((*exec)->fds[5] == 1)
        return (printf("this is a directory\n"), -1);
    if ((*exec)->fds[4] == 3)
        return (printf("ambigous redirection\n"), -1);
    if ((*exec)->fds[4] == 2)
        return (printf("no such a file or directory\n"), -1);
    if (handle_output_redirection(exec, flag) == -1)
        return -1;
    if (handle_append_redirection(exec , flag) == -1)
        return -1;
    if (handle_input_redirection(exec) == -1)
        return -1;
    handle_heredoc_redirection(exec);

    return 0;
}

void sigfork(int data)
{
    (void)data;
    exit_status = 130;
    printf("\n");
}
void ft_close(int *fd1 , int *fd2)
{
    close(*fd1);
    close(*fd2);
}
void ft_combine_free(void *s ,t_execution **exec, t_token **final)
{
    free(s);
    if(final)
    {
        return(free_stack(final), final = NULL , (void)0);
    }
    if(exec)
        return(free_stack(final), final = NULL , (void)0);
}
int ft_cmd_count(t_execution * curr)
{
    t_execution *temp;
    int         cmd_counter;

    temp = curr;
    cmd_counter = 0;
    while (temp)
    {
        cmd_counter++;
        temp = temp->next;
    }
    return (cmd_counter);
}
void execute_bins(t_execution **exec, char **env, t_env **env1 )
{
    t_execution *curr = *exec;
    char *fullcmd;
    pid_t *pids;
    int cmd_count;
    int i = 0;
    int prev_pipe[2] = {0, 1};
    int curr_pipe[2];
    int flag = 0;
    int tmp = 0;
    cmd_count = ft_cmd_count(curr);
    pids = malloc(sizeof(pid_t) * cmd_count);
    gc_add(0 , pids, NULL);
    while (curr && i < cmd_count)
    {
        if (i < cmd_count - 1)
            pipe(curr_pipe);
        if (cmd_count == 1 && check_builtins(curr))
            return (exit_status = execute_builtins(curr, env1, env), env = env_to_arr2(*env1) , gc_add(0 , env , NULL), (void)0);
        pids[i] = fork();
        signal(SIGQUIT , sig_handler1);
        signal(SIGINT, sigfork);
        if (pids[i] == 0)
        {
            signal(SIGINT, sig_heredoc);
            signal(SIGQUIT , SIG_DFL);
            if (redirect_io(&curr, &flag) == -1)
                return (exit_minishell(1) , (void)0);
            if (i > 0)
            {
                dup2(prev_pipe[0], STDIN_FILENO);
                ft_close(&prev_pipe[0] , &prev_pipe[1]);
            }
            if (i < cmd_count - 1)
            {
                if (flag == 0)
                    dup2(curr_pipe[1], STDOUT_FILENO);
                ft_close(&curr_pipe[0] , &curr_pipe[1]);
            }
            if (curr->cmd[0] == NULL)
                return (exit_minishell(1) ,(void)0);
            env = env_to_arr2(*env1);
            gc_add(0 , env, NULL);
            if (cmd_count > 1 && check_builtins(curr))
            {
                if (flag == 1)
                {
                    if (curr->fds[0] != 1)
                    {
                        dup2 (STDOUT_FILENO, curr->fds[0]);
                        close(STDOUT_FILENO);
                    }
                    if (curr->fds[2] != 1)
                    {
                        dup2 (STDOUT_FILENO, curr->fds[2]);
                        close(STDOUT_FILENO);
                    }
                }
                exit_status = execute_builtins(curr, env1, env);
                return (exit_minishell(0), (void)0);
            }
            else
            {
                fullcmd = find_path(curr->cmd[0], env);
                if((curr->cmd[0][0]) != '\0')
                {
                    struct stat data;
                    if (stat(fullcmd, &data) == 0 && S_ISDIR(data.st_mode))
                        return (printf("%s is directory\n", fullcmd) ,exit_minishell(126) , (void)0);
                    if (!fullcmd)
                    {
                        fprintf(stderr, "Command not found: %s\n", curr->cmd[0]);
                        exit_minishell(127);
                    }
                }
                if (execve(fullcmd, curr->cmd, env) == -1)
                    return (perror("minishell")  ,exit_minishell(126) ,(void)0);
            }
        }
        else
        {
            if (i > 0)
                ft_close(&prev_pipe[0] , &prev_pipe[1]);
            if (i < cmd_count - 1)
            {
                prev_pipe[0] = curr_pipe[0];
                prev_pipe[1] = curr_pipe[1];
            }
        }
        curr = curr->next;
        i++;
    }
    i = -1;
    int tmp1 = exit_status;
    while (++i < cmd_count)
       waitpid(pids[i], &exit_status, 0);
    if(WIFEXITED(exit_status))
        exit_status = (char)WEXITSTATUS(exit_status);
    tmp = exit_status;
    if(tmp1 == 130)
        exit_status = tmp1;
}

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

// char *find_env_variable2 (t_env *env, char *varname)
// {
//     while (env)
//     {
//         if (ft_strcmp(env->variable, varname) == 0)
//         {
//             return env->value;
//         }
//         env = env->next;
//     }
//     return (NULL);
// }

int execute_builtins(t_execution *exec  ,t_env **env, char **envs)
{
    (void) envs;
	int ret = 0;

     if(!*(exec->cmd))
            return (0);
	if (strncmp(exec->cmd[0], "echo", 5) == 0)
    {
		ret = my_echo(exec->fd_out, exec->cmd_len, exec->cmd);
    }
	if (strncmp (exec->cmd[0], "cd", 3) == 0)
    {
		ret = my_cd(exec , *env);
    }
	if (strncmp(exec->cmd[0], "pwd", 4) == 0)
    {
		ret = my_pwd(exec->fd_out, *env);
    }
	else if (strncmp (exec->cmd[0] , "env", 4) == 0)
    {
		ret = my_env(exec->fd_out, env);
    }
	else if (strncmp(exec->cmd[0] , "export", 7) == 0)
	{
        ret = my_export(exec , env, exec->fd_out);
    }
    else if (strncmp (exec->cmd[0] , "unset", 6) == 0)
    {
        ret = my_unset(&exec, env);
    }
    else if(!ft_strcmp(exec->cmd[0], "exit"))
    {
        my_exit(exec);
    }
    return ret;
}

int check_builtins(t_execution *exec)
{
	int ret = 0;
     if(!exec->cmd[0])
         return 0;
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
    if(ft_strchr(path_var , ':'))
        paths = ft_split(path_var, ':');
    else
    {
        paths = (char **)malloc(16);
        paths[0] = remove_quotes(path_var);
        paths[1] = NULL;

    }
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
            return (ft_free11(paths) ,full_command);
        free(full_command);
        i++;    
	}
    ft_free11(paths);
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


int handle_output_redirection(t_execution **exec, int *flag)
{
    if ((*exec)->fd_out != 1)
    {
        if ((*exec)->fflag == 1)
            return (printf("permission denied1\n"), -1);
        *flag = 1;
        dup2((*exec)->fd_out, STDOUT_FILENO);
        if ((*exec)->fd_out != STDOUT_FILENO)
            close((*exec)->fd_out);
    }
    return 0;
}

int handle_append_redirection(t_execution **exec)
{
    if ((*exec)->fd_append != 1)
    {
        if ((*exec)->fflag == 1)
            return (printf("permission denied\n"), -1);
        dup2((*exec)->fd_append, STDOUT_FILENO);
        close((*exec)->fd_append);
    }
    return 0;
}

int handle_input_redirection(t_execution **exec)
{
    if ((*exec)->fd_in != 0)
    {
        if ((*exec)->fd_in == -1 || (*exec)->fflag == 1)
        {
            printf("no such a file or directory\n");
            return -1;
        }
        dup2((*exec)->fd_in, STDIN_FILENO);
        close((*exec)->fd_in);
    }
    return 0;
}

int handle_heredoc_redirection(t_execution **exec)
{
    if ((*exec)->fd_heredoc != 0)
    {
        dup2((*exec)->fd_heredoc, STDIN_FILENO);
        close((*exec)->fd_heredoc);
    }
    return 0;
}

int redirect_io(t_execution **exec, int *flag)
{
    if ((*exec)->dflag == 1)
        return (printf("this is a directory\n"), -1);
    if ((*exec)->fflag == 3)
        return (printf("ambigous redirection\n"), -1);
    if ((*exec)->fflag == 2)
        return (printf("no such a file or directory\n"), -1);
    if (handle_output_redirection(exec, flag) == -1)
        return -1;
    if (handle_append_redirection(exec) == -1)
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
        free_stack(final);
    free_stack1(exec);
}
int ft_pip_count(t_execution * curr)
{
    t_execution *temp;
    int         pipe_counter;

    temp = curr;
    pipe_counter = 0;
    while (temp)
    {
        pipe_counter++;
        temp = temp->next;
    }
    return (pipe_counter);
}
void execute_bins(t_execution **exec, char **env, t_env **env1 )
{
    t_execution *curr = *exec;
    char *fullcmd;
    pid_t *pids;
    int pipe_count;
    int i = 0;
    int prev_pipe[2] = {0, 1};
    int curr_pipe[2];
    int flag = 0;

    pipe_count = ft_pip_count(curr);
    pids = malloc(sizeof(pid_t) * pipe_count);
    if (!pids)
        return;
    while (curr && i < pipe_count)
    {
        if (i < pipe_count - 1)
            pipe(curr_pipe);
        if (!curr->next &&  check_builtins(curr))
            return (exit_status = execute_builtins(curr, env1, env), free(pids), env = env_to_arr2(*env1), (void)0);
        pids[i] = fork();
        signal(SIGQUIT , sig_handler1);
        signal(SIGINT, sigfork);
        if (pids[i] == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT , SIG_DFL);
            if (redirect_io(&curr, &flag) == -1)
                return (free(pids) , exit(1) , (void)0);
            if (i > 0)
            {
                dup2(prev_pipe[0], STDIN_FILENO);
                ft_close(&prev_pipe[0] , &prev_pipe[1]);
            }
            if (i < pipe_count - 1)
            {
                if (flag == 0)
                    dup2(curr_pipe[1], STDOUT_FILENO);
                ft_close(&curr_pipe[0] , &curr_pipe[1]);
            }
            if (curr->cmd[0] == NULL)
                return (ft_combine_free(pids , exec, NULL) , exit(1), (void)0);
            env = env_to_arr2(*env1);
            if (curr->next && check_builtins(curr))
            {
                exit_status = execute_builtins(curr, env1, env);
                return (ft_combine_free(pids, exec , NULL), exit (0), (void)0);
            }
            else
            {
                fullcmd = find_path(curr->cmd[0], env);
                if (!fullcmd)
                {
                    exit_status = 127;
                    fprintf(stderr, "Command not found: %s\n", curr->cmd[0]);
                    return (free(pids) ,ft_combine_free(fullcmd , exec , NULL), exit(1), (void)0);
                }
                struct stat data;
                if (stat(fullcmd, &data) == 0 && S_ISDIR(data.st_mode))
                    return (printf("%s is directory\n", fullcmd), exit(1) , (void)0);
                if(!curr->cmd)
                    curr->cmd[0] = ft_strdup("");
                if (execve(fullcmd, curr->cmd, env) == -1)
                {
                    free(pids);
                    return (free_stack1(exec), perror("minishell"),free(fullcmd), exit(1),(void)0);
                }
                free(fullcmd);
            }
        }
        else
        {
            if (i > 0)
                ft_close(&prev_pipe[0] , &prev_pipe[1]);
            if (i < pipe_count - 1)
            {
                prev_pipe[0] = curr_pipe[0];
                prev_pipe[1] = curr_pipe[1];
            }
        }
        curr = curr->next;
        i++;
    }
    i = -1;
    while (++i < pipe_count)
        waitpid(pids[i], &exit_status, 0);
    WIFEXITED(exit_status);
    ft_combine_free(pids, exec, NULL);
}

#include "../includes/minishell.h"

t_env *find_variable(t_env *env, const char *variable_name)
{
    while (env)
    {
        if (strcmp(env->variable, variable_name) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}

void update_env_value(t_env *env, const char *variable_name, const char *new_value)
{
    t_env *var = find_variable(env, variable_name);

    if (var)
    {
        free(var->value);
        var->value = strdup(new_value);
    }
}

void update_oldpwd(t_env *env, const char *old_pwd)
{
    update_env_value(env, "OLDPWD", old_pwd);
}

void update_pwd(t_env *env)
{
    char cwd[4096];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_env_value(env, "PWD", cwd);
    else
        perror("getcwd error");
}

int check_path (char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) != 0)
    {
        printf("Error:\n");
        return -1;
    }
    else if (S_ISREG(path_stat.st_mode))
    {
        printf("not a directory: %s\n", path);
    }
    else
    {
        printf("cd: no such file or directory: %s.\n", path);
        return -1;
    }
    return 0;
}
char *find_env_variable2 (t_env *env, char *varname)
{
    while (env)
    {
        if (ft_strcmp(env->variable, varname) == 0)
        {
            return env->value;
        }
        env = env->next;
    }
    return (NULL);
}

int my_cd(t_execution *exec , t_env *env)
{
    char old_pwd[4096];

    if (!exec->cmd[1])
    {
        chdir(find_env_variable2(env, "HOME"));
        return 1;
    }

    // int i = check_path(exec->av[1]);

    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("getcwd error");
        return 1;
    }

    if (chdir(exec->cmd[1]) != 0)
    {
        perror("cd");
        return 1;
    }

    update_oldpwd(env, old_pwd);
    update_pwd(env);

    return 0;
}

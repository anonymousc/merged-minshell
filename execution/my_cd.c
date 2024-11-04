#include "builtins.h"

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

int my_cd(t_exec *exec)
{
    char old_pwd[4096];

    if (exec->ac != 2)
    {
        printf("cd: wrong number of arguments\n");
        return 1;
    }

    int i = check_path(exec->av[1]);

    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("getcwd error");
        return 2;
    }

    if (chdir(exec->av[1]) != 0)
    {
        perror("cd");
        return 3;
    }

    update_oldpwd(exec->env, old_pwd);
    update_pwd(exec->env);

    return 0;
}

int main (int ac, char **av, char **env)
{
    t_exec *exec = malloc (sizeof(t_exec));
    exec->env_orginal = env;
    t_env *test = make_env(exec);
    exec->ac = ac;
    exec->av = av;
    exec->env = test;
    printf ("----------------------before cd ------------------\n");
    my_env(test);
    my_cd(exec);
    printf ("----------------------after cd ------------------\n");
    my_env(test);
    printf ("-------------------------------------------------\n");
    my_pwd();
}
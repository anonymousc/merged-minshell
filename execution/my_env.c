#include "builtins.h"

t_env *make_env(char **env_orginal) 
{
    int i = 0;
    t_env *envir = NULL;
    t_env *new;
    char *delimiter;
    while (env_orginal && env_orginal[i])
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return NULL;
        delimiter = strchr(env_orginal[i], '=');
        if (!delimiter)
            free(new); 
        new->variable = strndup(env_orginal[i], delimiter - env_orginal[i]);
        if (!new->variable)
        {
            free(new);  
            return NULL;
        }
        new->value = strdup(delimiter + 1);
        if (!new->value)
        {
            free(new->variable);
            free(new);
            return NULL;
        }
        new->next = NULL;
        add_back(&envir, new);
        i++;
    }
    return envir;
}

int my_env(int fd, t_env *env) 
{
    while (env) 
    {
        ft_printf(fd, "%s=%s\n", env->variable, env->value);
        env = env->next;
    }
    return 0;
}

void free_env(t_env *env)
{
    t_env *temp;
    while (env)
    {
        temp = env;
        env = env->next;
        free(temp->variable);
        free(temp->value);
        free(temp);
    }
}

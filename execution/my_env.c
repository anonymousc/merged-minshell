#include "../includes/minishell.h"

t_env *make_env(char **env_original)
{
    int i = 0;
    t_env *envir = NULL;
    t_env *new;
    char *delimiter;

    while (env_original && env_original[i])
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return NULL;

        delimiter = strchr(env_original[i], '=');
        if (!delimiter)
        {
            // free_env(new);
            return NULL;
        }

        new->variable = strndup(env_original[i], delimiter - env_original[i]);
        if (!new->variable)
        {
            // free_env(new);
            return NULL;
        }

        new->value = strdup(delimiter + 1);
        if (!new->value)
        {
            // free_env(new);
            return NULL;
        }
        new->next = NULL;
        add_back(&envir, new);
        i++;
    }
    return envir;
}

int my_env(int fd, t_env **env)
{
    t_env *curr = *env;
    while (curr)
    {
        ft_printf(fd, "%s=%s\n", curr->variable, curr->value);
        curr = curr->next;
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
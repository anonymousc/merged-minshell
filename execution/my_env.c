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
        gc_add(0 , new, NULL);
        delimiter = ft_strchr(env_original[i], '=');
        if (!delimiter)
            return (NULL);
        new->variable = ft_strndup(env_original[i], delimiter - env_original[i]);
        gc_add(0, new->variable, NULL);
        if (!new->variable)
            return (NULL);
        char *tmp = ft_strdup(delimiter + 1);
        new->value = tmp;
        if (!new->value)
            return (NULL);
        new->next = NULL;
        add_back(&envir, new);
        gc_add(0, tmp, NULL);
        i++;
    }
    return envir;
}

int my_env(int fd, int fda, t_env **env)
{
    t_env *curr = *env;
    while (curr)
    {
        if (curr->value[0] == '\0' || curr->variable[0] == '#') 
        {
            curr = curr->next;
            continue;
        }
        if(fda == 1)
            ft_printf(fd, "%s=%s\n", curr->variable, curr->value);
        else
            ft_printf(fda, "%s=%s\n", curr->variable, curr->value);
        curr = curr->next;
    }
    return 0;
}

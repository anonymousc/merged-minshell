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
            return (/*free_env(new),*/NULL);
        new->variable = strndup(env_original[i], delimiter - env_original[i]);
        if (!new->variable)
            return (/*free_env(new),*/NULL);
        new->value = strdup(delimiter + 1);
        if (!new->value)
            return (/*free_env(new),*/NULL);
        new->next = NULL;
        add_back(&envir, new);
        i++;
    }
    printf("exited -------------\n");
    for (t_env *tmp = envir; tmp ; tmp=tmp->next)
        printf("%s = [%s]\n", tmp->variable, tmp->value);
    printf("exited-------------\n");
    return envir;
}

int my_env(int fd, int fda, t_env **env)
{
    t_env *curr = *env;
    // my_unset(NULL, env);
    int i = 1;
    if(i > 1)
    {
        i--;
        my_env(1 , 2 , env);
    }
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
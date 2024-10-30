#include "builtins.h"

t_env *make_env(t_exec *exec) 
{
    int i = 0;
    t_env *envir = NULL;
    t_env *new;
    char *delimiter;
    while (exec->env_orginal && exec->env_orginal[i])
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return NULL;
        delimiter = strchr(exec->env_orginal[i], '=');
        if (!delimiter)
            free(new); 
        new->variable = strndup(exec->env_orginal[i], delimiter - exec->env_orginal[i]);
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
    exec->env = envir;
    return envir;
}

int my_env(t_env *env) 
{
    while (env) 
    {
        printf("%s=%s\n", env->variable, env->value);
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

// int main(int argc, char **argv, char **envp)
// {
//     t_execution *exec = malloc (sizeof (t_execution));
//     exec->env_orginal = envp;
//     t_env *env = make_env(exec);
//     if (!env)
//     {
//         printf("Failed to create environment list\n");
//         return 1;
//     }

//     my_env(env);

//     free_env(env);
//     return 0;
// }
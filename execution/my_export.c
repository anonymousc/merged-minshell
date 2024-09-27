#include "builtins.h"

int is_alpha (int c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_alphanum(int c)
{
    return (is_alpha(c) || (c >= '0' && c <= '9'));
}

void swap(char **s1, char **s2)
{
    char *tmp;
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

char **sort_strings(char **str, int len) 
{
    int i = 0;
    int j;
    while (i < len - 1) 
    { 
        j = i + 1;
        while (j < len) 
        {
            if (strcmp(str[i], str[j]) > 0) 
            {
                swap(&str[i], &str[j]);
            }
            j++;
        }
        i++;
    }
    return str;
}

t_env *find_env_variable (t_env *env, char *varname)
{
    while (env)
    {
        if (strcmp(env->variable, varname) == 0)
        {
            return env;
        }
        env = env->next;
    }
    return NULL;
}

t_env *creat_env_var (char *varname, char *value)
{
    t_env *new_var = malloc(sizeof(t_env));

    new_var->variable = varname;
    new_var->value = value;
    new_var->next = NULL;
    return new_var;
}

int is_valid_identifier (char *arg)
{
    int  i = 1;
    if (!is_alpha(arg[0]) && arg[0] != '_')
    {
        printf ("%s not a valid identifier\n", arg);
        return -1;
    }
    while (arg[i] && (arg[i] != '+' && arg[i] != '='))
    {
        if (!is_alphanum(arg[i]) && arg[i] != '_')
        {
            printf ("%s not a valid identifier\n", arg);
            return -1;
        }
        i++;
    }
    return 0;
}

int update_existing_var(t_env *existing, char *value, int is_append)
{
    char *new_value;

    if (is_append)
    {
        new_value = ft_strjoin(existing->value, value);
        if (!new_value)
            return 0; 
        free(existing->value);
        existing->value = new_value;
    }
    else
    {
        new_value = ft_strdup(value);
        if (!new_value)
            return 0;
        free(existing->value);
        existing->value = new_value;
    }
    printf("Updated: %s=%s\n", existing->variable, existing->value);
    return 1;
}


int handle_existing_var(t_execution *exec, char *var_name, char *value, int is_append)
{
    t_env *existing = find_env_variable(exec->env, var_name);
    t_env *new_var;

    if (existing)
    {
        return update_existing_var(existing, value, is_append);
    }
    else
    {
        if (is_append)
            new_var = creat_env_var(var_name, value);
        else
            new_var = creat_env_var(var_name, value); 

        if (!new_var)
            return 0;

        add_back(&(exec->env), new_var);
        printf("Exported: %s=%s\n", var_name, value);
    }
    return 1;
}

int export_with_value(t_execution *exec, char *arg, char *equal, char *plus)
{
    int is_append = (plus && plus + 1 == equal);
    int name_len;

    if (is_append)
        name_len = plus - arg;
    else
        name_len = equal - arg;

    char *var_name = malloc(name_len + 1);
    if (!var_name)
        return 0;

    strncpy(var_name, arg, name_len);
    var_name[name_len] = '\0';

    char *value = equal + 1;

    if (!handle_existing_var(exec, var_name, value, is_append))
    {
        free(var_name);
        return 0;
    }

    // free(var_name);
    return 1;
}

int export_without_value(t_execution *exec, char *arg)
{
    t_env *existing = find_env_variable(exec->env, arg);
    t_env *new_var;

    if (!existing)
    {
        new_var = creat_env_var(arg, "");
        if (!new_var)
            return 0;

        add_back(&(exec->env), new_var);
        printf("Exported: %s\n", arg);
    }
    else
        printf("Already exported: %s\n", arg);

    return 1;
}

int process_export_arg(t_execution *exec, char *arg)
{
    char *equal = strchr(arg, '=');
    char *plus = strchr(arg, '+');

    if (!equal)
    {
        return export_without_value(exec, arg);
    }
    else
    {
        return export_with_value(exec, arg, equal, plus);
    }
}

int my_export(t_execution *exec)
{
    int i = 1;
    while (exec->av[i])
    {
        char *arg = exec->av[i];

        // if (is_valid_identifier(arg) < 0)
            // return 1;

        if (!process_export_arg(exec, arg))
            return 1;

        i++;
		printf("data == %s\n", arg);
    }
    return 0;
}

// int main(int ac, char **av, char **env)
// {
//     t_execution *exec = malloc(sizeof(t_execution));
//     exec->ac = ac;
//     exec->av = av;
//     exec->env_orginal = env;
//     t_env * envir = make_env(exec);
//     exec->env = envir;

//     int result = my_export(exec);
//     if (result != 0)
//     {
//         printf("Export failed\n");
//         return 1;
//     }
//     my_env(exec->env);
//     return 0;
// }

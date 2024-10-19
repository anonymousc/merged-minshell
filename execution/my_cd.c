#include "builtins.h"

// char *home_path (char *path)
// {
//     char *home = getenv("HOME");
//     char *parsed_path;

//     if (path[0] == '~')
//     {
//         parsed_path = malloc(strlen(home) + strlen(path));
//         if (!parsed_path)
//             return NULL;
//         strcpy(parsed_path, home);
//         strcat(parsed_path, path + 1);

//         return parsed_path;
//     }
//     else
//         return path;
// }


// void change_dir(char *path, bool print)
// {
//     char *cwd;
//     char buff[2024];
//     int mode = 0;

//     if (!chdir(path))
//     {
//         if (print)
//         {
//             printf ("%s\n", path);
//             setenv("OLDPWD", cwd, 1);
//         }
//     }
//     else
//     {
//         printf ("cd : ");
//         if (access(path, F_OK))
//             printf ("no such file or directory");
//         else if (access(path, R_OK))
//             printf ("reading denied");
//         else
//             printf ("not a directory");
//         printf ("%s\n", path);
//     }
// }

// int main(int argc, char **argv) 
// {

//     if (!argv[1])
//         return 1;
//     else
//         change_dir (argv[1], 1);  
//     return 0;
// }



// void update_oldpwd (t_env *env)
// {
//     char *str;

//     while (env)
//     {
//         if (strncmp (env->variable, "PWD=", 4))
//         {
//             str = env->variable + 4;
//             break;
//         }
//         env = env->next;
//     }
//     if (str)
//     {
//         setenv("OLDPWD", str, 1); //todo
//     }
// }

// void update_pwd(t_env *env, char* newpath)
// {
//     char *pwd = NULL;

//     pwd = malloc(strlen("PWD=") + strlen(newpath));
//     if (!pwd)
//         return;
    
//     strcpy(pwd, "PWD=");
//     strcat(pwd, newpath);

//     while (env)
//     {
//        if (strncmp(env->variable, "PWD=", 4) == 0)
//         {
//             free(env->variable);
//             env->variable = pwd;
//             return;
//         }
//         env = env->next;
//     }
// }

// void my_cd(t_env *env, int ac , char **av)
// {
//     char cwd[1024];

//     if (ac == 2)
//     {
//         if (getcwd(cwd, sizeof(cwd)))
//             update_oldpwd(env);
//         if (chdir(av[1]) == 0)
//         {
//             printf ("path : %s\n", av[1]);
//             update_pwd(env, av[1]);
//         }
//         else
//             printf ("cd error\n");  
//     }
//     else
//         printf ("wrong number of arguments\n");
// }


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

    // Check if the path exists and retrieve its status
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

int my_cd(t_execution *exec)
{
    char old_pwd[4096];

    if (exec->ac != 2)
    {
        printf("cd: wrong number of arguments\n");
        return 1;
    }

    // int i = check_path(exec->av[1]);

    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("getcwd error");
        return 2;
    }

    if (chdir(exec->av[1]) != 0)
    {
        perror("chdir");
        return 3;
    }

    update_oldpwd(exec->env, old_pwd);
    update_pwd(exec->env);

    return 0;
}

// int main (int ac, char **av, char **env)
// {
//     t_execution *exec = malloc (sizeof(t_execution));
//     exec->env_orginal = env;
//     t_env *test = make_env(exec);
//     exec->ac = ac;
//     exec->av = av;
//     exec->env = test;
//     // printf ("----------------------before cd ------------------\n");
//     // my_env(test);
//     my_cd(exec);
//     // printf ("----------------------after cd ------------------\n");
//     // my_env(test);
//     // printf ("-------------------------------------------------\n");
//     my_pwd();
// }
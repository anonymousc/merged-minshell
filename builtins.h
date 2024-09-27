#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

typedef struct s_env
{
    char *variable;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_execution
{
    int ac;
    char **env_orginal;
    char **av;
    char *input;
    t_env  *env;
} t_execution;



//utils
int list_len(t_env *env);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char sep);
size_t	ft_strlen(char *str);
void print_env(t_env *env);
t_env * make_env(t_execution *exec);
char *ft_strchr(char *str, int c);
char *ft_strndup (char *str, size_t n);
char *ft_strdup (char *str);
void add_back(t_env **envir, t_env *var);
t_env *get_last(t_env *envir);
//my_env
void my_env(t_env *env);
void free_env(t_env *env);
//pwd
void my_pwd();
//export
// int my_export(t_env **env, char **args);
int my_export(t_execution *exec);
//cd
int my_cd(t_execution *exec);
#endif
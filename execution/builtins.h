#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include "../src/libft/libft.h"
#include "../includes/minishell.h"

typedef struct s_env
{
    char *variable;
    char *value;
    struct s_env *next;
} t_env;


//utils
int     list_len(t_env *env);
char	*ft_strjoin(char *s1, char *s2);
size_t	count_words(char const *str, char sep);
char	**ft_splita(char const *s, char sep);
void	free_split(char **s, int n);
// size_t	ft_strlen(char *str);
void    print_env(t_env *env);
t_env   *make_env(char **envp);
// char *ft_strchr(char *str, int c);
char    *ft_strndup (char *str, size_t n);
char    *ft_strdup (char *str);
void    add_back(t_env **envir, t_env *var);
t_env   *get_last(t_env *envir);
//my_env
void    free_env(t_env *env);
int     my_env(int fd, int fda, t_env **env);
void    free_env(t_env *env);
//pwd
int     my_pwd(int fd ,int fda, t_env *env);
//export
int     my_export(t_execution *exec , t_env **env, int fd , int fda);
char    **env_to_arr2(t_env *env);
char    **env_to_arr(t_env *env);
t_env   *find_env_variable (t_env *env, char *varname);
//unset
int     my_unset(t_execution **exec, t_env **env);
//cd
int     my_cd(t_execution *exec , t_env *env);
//echo
int     my_echo (int fd, int fda, int ac, char **av);
char 	*find_env_variable2 (t_env *env, char *varname);
//execute builtins
int     execute_builtins(t_execution *exec, t_env **env, char **envs);
int check_builtins(t_execution *exec);
void    execute_bins(t_execution **exec, char **env, t_env **env1);

t_env **update_env(t_env **env);
void my_exit(t_execution *list);
void _update_pwd(t_env *env);
#endif
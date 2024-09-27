/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:21:40 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/24 18:40:10 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

/* ******** C libraries ******** */

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include "../src/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>

/* ******** DEFINITIONS ********* */

# define PATH_MAX       4096

/* ****************************** */

/* ********** TYPEDEFS ********** */

typedef struct	s_syntax
{
	int iter;
	int flag;
	char c;
	int start;
	int end;
	
}				t_syntax;

typedef	struct	s_AST
{
	char			*data;
	int				fd;
	
	struct s_AST	*right;

}				t_AST;

/* ****************************** */

/*  ********* BULTINS *********  */

void	ft_pwd(void);
void	ft_env(t_env **env);
char	*quotes_holder(char *line);
/* **************************** */
/*  ******** PARSING *********  */

char *check_qoutes(char *s);
int is_quotes(char c);

/* **************************** */

/*  ******** PARSING *********  */

t_env		**fill_env(char **envp, t_env **env);
char		**parser(char **av);
char		*check_syntax(char *s);
t_token 	**ft_fill(char *line);
// void		init_token s(char *str);
void		print_tokens(t_token *list);
void		free_env(t_env **stack);
char 		*retline(void);
void		sig_handler(int test);
void		sig_handler1(int test);
char		*quotes_holder2(char *s, int  *i);
void		skip_space2(char *str , int *pos);
Token		get_token (char *str);
int			is_separators(char c);
char		**split_to_lex(char const *s);
int			is_quotes(char c);
void		tokenization(char **line , t_token **fill_line);
/* **************************** */

#endif
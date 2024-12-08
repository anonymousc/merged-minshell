/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:21:40 by hatalhao          #+#    #+#             */
/*   Updated: 2024/12/07 20:53:53 by aessadik         ###   ########.fr       */
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
# include "../execution/builtins.h"

/* ******** DEFINITIONS ********* */

# define PATH_MAX       4096

/* ****************************** */

/* ********** TYPEDEFS ********** */

typedef struct	s_syntax
{
	int s_q;
	int d_q;
	int iter;
}				t_syntax;

typedef struct s_norminette
{
	int i;
	int flag;
}			t_norminette;

typedef struct s_files
{
	int file_out;
	int file_in;
	int file_append;
	int file_heredoc;
	int is_dir;
	int flag_error;

}				t_files;


extern int exit_status;
/* ****************************** */

/*  ********* BULTINS *********  */

char	*quotes_holder(char *line);
/* **************************** */
/*  ******** PARSING *********  */

char *check_qoutes(char *s);
int is_quotes(char c);

/* **************************** */

/*  ******** PARSING *********  */

char		**parser(char **av);
char		*check_syntax(char *s);
t_token 	**ft_fill(char *line);
// void		init_token s(char *str);
void		print_tokens(t_token *list);
// void		free_env(t_env **stack);
char 		*retline(void);
void		sig_handler(int test);
void		sig_handler1(int test);
char		*quotes_holder2(char *s, int  *i);
void		skip_space2(char *str , int *pos);
Token		get_token (char *str);
int			is_separators(char c);
char		**split_to_lex(char *s);
int			is_quotes(char c);
void		tokenization(char **line , t_token **fill_line);
void		sanitizer(t_token **fill_line);
int			check_syntax_extended (t_token **final);
t_token		*free_spaces (t_token *curr);
void		free_spaces2(t_token **head);
void		expander_final(t_token **final ,t_env *env);
/* **************************** */
// to remove
// int here_doc(t_token **final, int *fd);
int		here_doc(t_token **final ,t_env *env);
int		file_size(t_token **data);

//execution
// void execute_bins (t_execution **exec, char **env , t_env *env1);

// int execute_builtins(t_execution *exec, t_env *env1);

char *remove_quotes(char *s);

// char *find_env_variable2 (t_env *env, char *varname);


void ft_free11(char **s);

int check_in_db_or_sq(char *s);

char *expander(char *expansion, t_env *envp);
void for_execute(t_token **final, t_execution **data, t_env *env);
char	*before_dollar_word(char	*str);
char	*ft_strjoin2(char *s, char *s1);
void extra_sanitize(t_token **head);

void sig_heredoc(int test);

////////////////////////////////////////////////////////////
# define MEMGRP_DEFAULT 0

typedef struct s_memref
{
	void				*mem_data;
	struct s_memref		*next;
}						t_memref;

typedef struct s_memgroup
{
	int					id;
	t_memref			*mem_refs;
	struct s_memgroup	*next;
}						t_memgroup;

t_memgroup				**gc_get_memgroups(void);
t_memgroup				*gc_create_mem_group(int id);
t_memgroup				*gc_get_specific_memgroup(int id);
t_memref				**gc_get_memrefs(int id);
void					gc_free_memrefs(t_memref *mem_ref);
void					gc_free_specific_memref(t_memref **mem_ref_head,
							t_memref *mem_ref_to_free);
void					*gc_calloc(int mem_group_id, size_t count, size_t size,
							t_memref **store_memref);
void					*gc_malloc(int mem_group_id, size_t size,
							t_memref **store_memref);
void					gc_add(int mem_group_id, void *mem,
							t_memref **store_memref);
void					gc_add_double(int mem_group_id, void **mem,t_memref **store_memref);
void					gc_free_memgrp(int mem_group_id);
void					gc_free_all(void);
void					exit_minishell(int exit_code);
////////////////////////////////////////////////////////////
#endif
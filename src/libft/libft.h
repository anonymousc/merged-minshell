/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:16:47 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/27 18:44:33 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include "ft_printf/ft_printf.h"


///////DEFINITIONS/////

typedef enum
{
	PIPE = 1,
	REDIRECTION_OUT,
	REDIRECTION_IN,
	HEREDOC,
	APPEND,
	DOLLAR_SIGN,
	WORD,
	SYNTAX_ERROR_OUT,
	SYNTAX_ERROR_IN,
	SYNTAX_ERROR_PIPE,
	WHITESPACE

} Token;

// typedef	struct		s_env
// {
// 	char			*env;
// 	struct s_env	*next;

// }					t_env;

typedef	struct	s_Tokenization
{
	char					*data;
	Token					value;
	struct s_Tokenization	*next;

}		t_token;
typedef struct s_execution
{
	char 				**cmd;
	int 				fflag;
	int 				dflag;
	int					fd_in;
	int					fd_out;
	int					fd_append;
	int					fd_heredoc;
	// int					fd[2];
	// int					pid;
	struct s_execution	*next;
}					t_execution;

///////////////////////

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(char const *nptr);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(char const *s1, char const *s2, size_t n);
int		is_space(char c);
int		ft_strcmp(char *s1, char *s2);
char	*is_space_veta(char s);
void 	for_execute(t_token **final , t_execution **data);


char	*ft_itoa(int n);
char	*ft_strdup(char *src);
char	*ft_strchr(char const *s, int c);
char	*ft_strrchr(char const *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(char const *haystack, char const *needle, size_t n);
char	**ft_split(char const *s, char c);
char	**ft_split_set(char *str, char *charset);


void	ft_bzero(void *s, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	free_stack(t_token  **stack);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	split_to_fill(char *s , t_token  **fill);

size_t	ft_strlen(char const *str);
size_t	ft_strlcat(char *dest, char const *src, size_t size);
size_t	ft_strlcpy(char *dest, char const *src, size_t size);
size_t	word_count(char const *s, char c);
char **fri_ol(char **str);

// GET_NEXT_LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3

# endif

char	*get_new_line(char *s);
char	*ft_strjoin(char *s, char *s1);
int		find_newline(char *str);
char	*get_next_line(int fd);
char	*set_buffer(char *buffer, char *line);
char	*read_line(char *ret, int fd);
char	*ft_free(char *s);

//    LINKED LISTS

t_token  *ft_lstnew(char *content , Token t);
t_token  *ft_lstlast(t_token *lst);

void	ft_lstdelone(t_token  **lst);
void	ft_lstclear(t_token  **lst);
void	ft_lstadd_back(t_token  **lst, t_token *new);
void	ft_lstadd_front(t_token  *lst, t_token *new);
int		ft_lstsize(t_token  *lst);

#endif

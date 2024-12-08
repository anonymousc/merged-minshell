/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:16:47 by hatalhao          #+#    #+#             */
/*   Updated: 2024/12/07 20:50:37 by aessadik         ###   ########.fr       */
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
	WORD,
	WHITESPACE

} Token;

typedef	struct	s_Tokenization
{
	char					*data;
	Token					value;
	struct s_Tokenization	*next;

}		t_token;

typedef struct s_execution
{
	char 				**cmd;
	int					*fds;
	int					cmd_len;
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
void ft_combine_free(void *s ,t_execution **exec, t_token **final);


//    LINKED LISTS

t_token  *ft_lstnew(char *content , Token t);
t_token  *ft_lstlast(t_token *lst);

void	ft_lstdelone(t_token  **lst);
void	ft_lstclear(t_token  **lst);
void	ft_lstadd_back(t_token  **lst, t_token *new);
void	ft_lstadd_front(t_token  *lst, t_token *new);
int		ft_lstsize(t_token  *lst);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer_Tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:11:54 by aessadik          #+#    #+#             */
/*   Updated: 2024/09/24 18:22:46 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}

int check_is_same_quotes2(char c1, char c2)
{
	return (c1 == c2);
}

char *quotes_holder(char *s)
{
	char	quote;
	
	quote = (*s)++;
	while (s && *s && !check_is_same_quotes2(*s, quote))
		s++;
	return (s);
}

char *quotes_holder2(char *s, int  *i)
{
	char	quote;
	
	(*i) = 0;
	quote = (*i)++;
	while (s && s[(*i)] && !check_is_same_quotes2(s[(*i)], quote))
		(*i)++;
	return (s);
}

char *is_tokens(char s)
{
	if(s == '|')
		return ("|");
	else if(s == '>')
		return (">");
	else if(s == '<')
		return ("<");
	return 0;
}

Token get_token (char *str)
{
	if (ft_strnstr(str,"|",1))
		return (PIPE);
	else if (ft_strnstr(str,"<<",2))
		return (HEREDOC);
	else if (ft_strnstr(str , ">>" , 2))
		return (APPEND);
	else if(ft_strnstr(str, ">" , 1))
		return (REDIRECTION_OUT);
	else if(ft_strnstr(str, "<" , 1))
		return(REDIRECTION_IN);
	else if(ft_strnstr(str , " " , 1) || ft_strnstr(str , "\n" , 1) || ft_strnstr(str , "\v" , 1) || ft_strnstr(str , "\t" , 1) || ft_strnstr(str , "\r" , 1))
		return (WHITESPACE);
	return WORD;
}
void	tokenization(char **line , t_token **fill_line)
{
	int i;
	
	i = -1;
	*fill_line = NULL;
	while (line && line[++i])
	{

		ft_lstadd_back(fill_line , ft_lstnew(line[i] , get_token(line[i])));
	}
}

void sanitizer(t_token **fill_line) 
{
	t_token *data;
	t_token *tmp;

	data = *fill_line;
    while (data && (data)->next) 
	{
        if ((data)->value == WORD && (data)->next->value == WORD) 
		{
			tmp = data->next;
            (data)->data = ft_strjoin((data)->data, (data)->next->data);
            (data)->next = (data)->next->next;
            free(tmp);
        } 
		else 
            data = (data)->next;
    }
	fill_line = &data;
}

// to remove or enhace
void	ft_lstadd_back_exec(t_execution  **stacks, t_execution  *new)
{
	t_execution 	*head;

	if (!stacks || !*stacks)
	{
		*stacks = new;
		return ;
	}
	head = *stacks;
	while (head->next)
		head = head->next;
	head->next = new;
	new->next = NULL;
}

t_execution  *ft_lstnew_exec(char **cmd)
{
	t_execution   *list;

	list = (t_execution  *) malloc (sizeof(t_execution ));
	if (!list)
		return (NULL);
	list->cmd = cmd;
	list->next = NULL;
	return (list);
}


t_execution **for_execute(t_token **final , t_execution **data)
{
	t_token *curr = *final;
	t_token *tmp = curr;
	char **cmd;
	int wc = 0;

	while (tmp)
	{
		if(tmp->value == WORD)
			wc++;
		tmp = tmp->next;
	}
	cmd = (char **)malloc(sizeof(char *) * (wc + 1));
	*cmd = NULL;
	int i = 0;
	while (curr)
	{
		if(curr->value == WORD)
		{
			cmd[i] = curr->data;
			i++;
		}
		curr = curr->next;	
	}
	cmd[wc] = NULL;
	*data = ft_lstnew_exec(cmd);
	return data;
}

void here_doc(t_token **final)
{
	int fd[2];
	char *read;
	char *line;
	int pid;
	t_token *curr = *final;
	if (curr->value == HEREDOC)
	{
		char *delim = curr->next->data;
		pipe(fd);
		pid = fork();

		if (pid == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			while (line = get_next_line(fd[0]))
			{
				if (strncmp(line , delim, strlen(delim)))
				{
					close(fd[0]);
					return 1;
				}
			}
		}
		wait(NULL);
		close (fd[0]);
		close(fd[1]);
	}
}
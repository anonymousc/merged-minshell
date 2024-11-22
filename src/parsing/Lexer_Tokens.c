/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer_Tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:11:54 by aessadik          #+#    #+#             */
/*   Updated: 2024/10/27 23:21:16 by kali             ###   ########.fr       */
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
		ft_lstadd_back(fill_line , ft_lstnew(line[i] , get_token(line[i])));
}

void free_spaces2(t_token **head)
{
    t_token* current = *head;
    t_token* tmp;

    while (current) 
	{
        if (current->value == WHITESPACE) 
		{
            tmp = current;
            current = current->next;

            if (tmp == *head) 
                *head = current;
			else 
			{
                t_token* prev = *head;
                while (prev && prev->next != tmp) 
                    prev = prev->next;
                if (prev) 
                    prev->next = current;
            }

            free(tmp);
        } 
		else 
            current = current->next;
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

// to remove or enhance

// int file_size(t_token **data)
// {
// 	t_token *curr = *data;
// 	int wc = 0;
// 	while (curr)
// 	{
// 		if(curr && curr->value == REDIRECTION_OUT)
// 			wc++;
// 		curr = curr->next;
// 	}
// 	return wc;
// }

void	ft_lstadd_back_exec(t_execution  **stacks, t_execution  *new)
{
	t_execution 	*head;

	if (!*stacks)
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

t_execution  *ft_lstnew_exec(char **cmd, int fd_in , int fd_out ,int fd_append , int fd_heredoc, int flag, int dflag)
{
	t_execution   *list;

	list = (t_execution  *) malloc (sizeof(t_execution ));
	if (!list)
		return (NULL);
	list->cmd = cmd;
	list->fd_in = fd_in;
	list->fd_out = fd_out;
	list->fd_append = fd_append;
	list->fd_heredoc = fd_heredoc;
	list->fflag = flag;
	list->dflag = dflag;
	list->next = NULL;
	return (list);
}

int count_cmds(t_token **data)
{
	int wc = 0;
	t_token *curr = *data;
	while (curr)
	{
		if(curr && (curr->value == REDIRECTION_IN || curr->value == REDIRECTION_OUT))
			curr = curr->next->next;
		if(curr && curr->value == WORD)	
			wc++;
		if(curr)
			curr = curr->next;
	}
	return wc;
}

void for_execute(t_token **final, t_execution **data , int *expansion)
{
	struct stat dstat;
    t_token *curr = *final;
	(void)expansion;
    *data = NULL;
    while (curr)
    {
        int word_count = 0;
        t_token *temp = curr;
        while (temp && temp->value != PIPE)
        {
            if (temp->value == WORD)
                word_count++;
            temp = temp->next;
        }
        if (word_count == 0)
        {
            curr = curr->next;
            continue;
        }
        char **cmd = (char **)malloc(sizeof(char *) * (word_count + 1));
       	int k = -1;
	   	while(++k <= word_count)
	   		cmd[k] = NULL;
        int i = 0;
        int fd_in = 0;
		int fd_append = 1;
		int fd_heredoc = 0;
		int fd_out = 1;
		int fflag = 0;
		int dflag = 0;
        while (curr && curr->value != PIPE)
        {
            if (!curr->data)
            {
                curr = curr->next;
                continue;
            }
            if (curr->value == REDIRECTION_IN)
            {
				if (curr->next->value == REDIRECTION_OUT && !fflag)
				{
					open(curr->next->next->data , O_CREAT | O_RDWR | O_TRUNC, 0666);
					curr = curr->next->next;
				}
                if (curr->next && curr->next->data)
                {
                    fd_in = open(curr->next->data, O_RDONLY, 0444);
					if (fd_in == -1)
					{
						fflag = 1;
					}
					else if (!ft_strncmp(curr->next->data, "/dev/stdin" , ft_strlen("/dev/stdin")))
						fd_in--;
					curr = curr->next;
                }
            }
            else if (curr->value == REDIRECTION_OUT && !dflag)
            {
                if (curr->next && curr->next->data)
                {
					if (stat(curr->next->data , &dstat) > -1)
					{
						if (S_ISDIR(dstat.st_mode))
						{
							dflag = 1;
						}
					}
					if(*(curr->next->data) && *(curr->next->data) != '\v')
					{
						fd_out = open(curr->next->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
						if(access(curr->next->data , R_OK | W_OK) == -1)
							fflag = 1;
						if (!ft_strncmp(curr->next->data, "/dev/stdout" , ft_strlen("/dev/stdout")) && !curr->next->next)
							fd_out--;
					}
					else
						fflag = 2 + (ft_strchr(curr->next->data,'\v') == NULL);
                    curr = curr->next;
                }
            }
			else if(curr->value == HEREDOC)
			{
				if(curr->next && curr->next->data)
				{
					fd_heredoc = here_doc(&curr);
					curr = curr->next;
				}
			}
			else if(curr->value == APPEND)
			{
				if (curr->next && curr->next->data)
                {
					fd_append = open(curr->next->data, O_CREAT | O_RDWR | O_APPEND, 0666);
					if(access(curr->next->data , R_OK | W_OK) == -1)
						fflag = 1;
					curr = curr->next;
				}
			}
			// else if(curr->value == WORD && *expansion == 0)
			// {
			// 	cmd = ft_split(curr->data , ' ');
			// }
            else if (curr->value == WORD && i < word_count)
            {
					cmd[i] = strdup(curr->data);
                	i++;
            }
			for (int i = 0; cmd[i]; i++)
				printf("cmd[%d] == |%s|\n",i , cmd[i]);
			
            curr = curr->next;
        }
        t_execution *new_cmd = ft_lstnew_exec(cmd, fd_in, fd_out ,fd_append , fd_heredoc, fflag, dflag);
		// ft_free11(cmd);
		if (!*data)
            *data = new_cmd;
        else
            ft_lstadd_back_exec(data, new_cmd);
        if (curr && curr->value == PIPE)
            curr = curr->next;
    }
}
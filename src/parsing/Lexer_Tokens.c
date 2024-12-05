/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer_Tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:11:54 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/01 23:03:00 by kali             ###   ########.fr       */
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

t_execution  *ft_lstnew_exec(int *fds, char **cmd, int cmdlen)
{
	t_execution   *list;

	list = (t_execution  *) malloc (sizeof(t_execution ));
	if (!list)
		return (NULL);
	list->cmd = cmd;
	list->fds = fds;
	list->cmd_len = cmdlen;
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
int cmd_len (char **cmd)
{
	int i;

    i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static int count_words1(t_token *tokens)
{
    int word_count = 0;
    t_token *temp = tokens;

    while (temp && temp->value != PIPE)
    {
        if (temp->value == WORD)
            word_count++;
        temp = temp->next;
    }
    return (word_count);
}

static char **init_cmd_array(int word_count)
{
    char **cmd;
    int k;

    cmd = (char **)malloc(sizeof(char *) * (word_count + 1));
    k = -1;
    while (++k <= word_count)
        cmd[k] = NULL;
    return cmd;
}

int *init_fds(int *array)
{
    int i;

    i = 0;
    array = malloc(sizeof(int) * 7);
    if(!array)
        return NULL;
    while (i < 7)
    {
        if(i == 0 || i == 2)
            array[i] = 1;
        else
            array[i] = 0;
        i++;
    }
    return array;
}

static int handle_input_redirection(t_token **curr, int *fd_out, int *fd_append)
{
    int fd_in;

    fd_in = 0;
    if ((*curr)->next && (*curr)->next->data)
    {
        fd_in = open((*curr)->next->data, O_RDONLY, 0444);
        if (fd_in == -1)
        {
            *fd_out = -1;
            *fd_append = -1;
        }
        else if (!ft_strncmp((*curr)->next->data, "/dev/stdin", ft_strlen("/dev/stdin")))
            fd_in--;
        *curr = (*curr)->next;
    }
    return fd_in;
}

static int handle_output_redirection(t_token **curr, int *fflag, int *dflag)
{
    struct stat dstat;
    int fd_out = 1;

    if ((*curr)->next && (*curr)->next->data)
    {
        if (stat((*curr)->next->data, &dstat) > -1)
            if (S_ISDIR(dstat.st_mode))
                *dflag = 1;
        if (*(*curr)->next->data)
        {
            fd_out = open((*curr)->next->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
            if (access((*curr)->next->data, R_OK | W_OK) == -1)
                *fflag = 1;
            if (!ft_strncmp((*curr)->next->data, "/dev/stdout",  ft_strlen("/dev/stdout")) && !(*curr)->next->next)
                fd_out--;
        }
        *curr = (*curr)->next;
    }
    return fd_out;
}

static t_execution *process_command_tokens(t_token **curr, t_env *env)
{
    int word_count = count_words1(*curr);
    if (word_count == 0)
        return NULL;
    char **cmd;
    int *fds;
    int i;
    int cmdlen;

    fds = NULL;
    cmd = init_cmd_array(word_count);
    (void)(i = 0 ,cmdlen = word_count, fds = init_fds(fds));
    while (*curr && (*curr)->value != PIPE)
    {
        if (!(*curr)->data)
        {
            *curr = (*curr)->next;
            continue;
        }
        if ((*curr)->value == REDIRECTION_IN)
            fds[1] = handle_input_redirection(curr, &fds[0], &fds[2]);
        else if ((*curr)->value == REDIRECTION_OUT && !fds[5])
            fds[0] = handle_output_redirection(curr, &fds[4], &fds[5]);
        else if ((*curr)->value == HEREDOC)
        {
            if ((*curr)->next && (*curr)->next->data)
                (void)(fds[3] = here_doc(curr, env), *curr = (*curr)->next);
                
        }
        else if ((*curr)->value == APPEND)
        {
            if ((*curr)->next && (*curr)->next->data)
            {
                if(fds[0] != 1 || fds[2] == 1)
                    fds[0] = open((*curr)->next->data, O_CREAT | O_RDWR | O_APPEND, 0666);
                else
                    fds[2] = open((*curr)->next->data, O_CREAT | O_RDWR | O_APPEND, 0666);
                if (access((*curr)->next->data, R_OK | W_OK) == -1)
                    fds[4] = 1;
                *curr = (*curr)->next;
            }
        }
        else if ((*curr)->value == WORD && i < word_count)
            cmd[i++] = ft_strdup((*curr)->data);
        *curr = (*curr)->next;
    }
    return ft_lstnew_exec(fds, cmd, cmdlen);
}

void for_execute(t_token **final, t_execution **data, t_env *env)
{
    t_token *curr = *final;
    *data = NULL;

    while (curr)
    {
        t_execution *new_cmd = process_command_tokens(&curr, env);
        
        if (new_cmd)
        {
            if (!*data)
                *data = new_cmd;
            else
                ft_lstadd_back_exec(data, new_cmd);
        }
        if (curr && curr->value == PIPE)
            curr = curr->next;
    }
}
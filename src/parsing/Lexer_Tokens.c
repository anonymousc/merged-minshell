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
		if(tmp->value == WORD || !((tmp->value == REDIRECTION_IN || tmp->value == REDIRECTION_IN) && tmp->next->value == WORD))
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

// void heredoc_child(t_token **final, int *num_pipes, int **pipes)
// {
// 	t_token *curr = *final;
//     char *line = NULL;
// 	int i = 0;

// 	while (i < *num_pipes)
// 	{
// 		close (pipes[i][1]);
// 		i++;
// 	}
// 	while (curr && curr->value == HEREDOC)
// 	{
// 		curr = free_spaces (curr->next);
// 		char *delim = curr->data;
// 		while (1)
// 		{		
// 			line = get_next_line(0);
// 			if (line == NULL) 
// 				return ;
// 			if (strncmp(line, delim, strlen(delim)) == 0)
// 			{
// 				free(line);
// 				return ;
// 			}
// 			free(line);
// 		}
// 		curr = curr->next;
// 	}
// 	while (i < *num_pipes)
// 	{
// 		close (pipes[i][0]);
// 		i++;
// 	}
// }

// int **creat_pipes (int *num_pipes)
// {
// 	int i = 0;
// 	int **pipes = (int **)malloc ((*num_pipes + 2) * sizeof (int *));
// 	if(!pipes)
// 		exit(1);
// 	while (i < *num_pipes)
// 	{
// 		pipes[i] = malloc (2 * sizeof(int));
// 		i++;
// 	}
// 	// pipes[(*num_pipes + 1)] = NULL;
// 	return pipes;
// }

// void wait_children (int *num_pipes)
// {
// 	int i = 0;

// 	while (i < *num_pipes)
// 	{
// 		wait (NULL);
// 		i++;
// 	}

// }

// void here_doc (t_token **final, int *num_pipes, int **pipes)
// {
// 	int id;
// 	int i = 0;

// 	while (i < *num_pipes)
// 	{
// 		id = fork();
// 		if (id == 0)
// 			heredoc_child(final, num_pipes, pipes);
// 		i++;
// 	}
// 	dup2(pipes[*num_pipes - 2][0], STDIN_FILENO);
// }

// int here_doc_final(t_token **final)
// {
// 	int pc = 0;
// 	int **pipes;

// 	t_token *curr = *final;
// 	while (curr)
// 	{
// 		if (curr && curr->value == HEREDOC)
// 			pc++;
// 		curr = curr->next;
// 	}
// 	pipes = creat_pipes(&pc);
// 	here_doc(final, &pc, pipes);
// 	wait_children(&pc);
// 	return 0;
// }

// void heredoc_child(t_token **final, int *num_pipes, int **pipes) {
//     t_token *curr = *final;
//     char *line = NULL;

//     for (int i = 0; i < *num_pipes; i++)
//     	close(pipes[i][1]);
//     while (curr) 
// 	{
// 		if(curr->value == HEREDOC)
// 		{
// 			curr = free_spaces(curr->next);
// 			char *delim = curr->data;
// 			printf ("curr  == |%s|\n", curr->data);
// 			while (1) 
// 			{
// 				line = get_next_line(0);
// 				if (line == NULL) 
// 					return;
// 				if (strncmp(line, delim, strlen(delim)) == 0) 
// 				{
// 					free(line);
// 					return;
// 				}
// 				free(line);
// 			}
// 		}
// 		curr = curr->next;
//     }

//     // Close read ends after use
//     for (int i = 0; i < *num_pipes; i++) 
//         close(pipes[i][0]);
// }

// void here_doc(t_token **final, int *num_pipes, int **pipes) 
// {
//     int id;
//     int i = 0;
// 	while(i < *num_pipes)
// 	{
//         id = fork();
//         if (id == 0) 
// 		{
//             heredoc_child(final, num_pipes, pipes);
//             return (void)0; // Ensure the child exits after completion
//         }
//         // Close both ends of the pipe in the parent after forking
//         close(pipes[i][1]);
//         close(pipes[i][0]);
// 		i++;
//     }
// 	// int test = (i != 0);
// 	// printf("|%d|\n" , i - (i != 0));
//     // Redirect the input for the last pipe
//     // if(pipes[i - test][0])
// 		// dup2(pipes[i  - 1][0], STDIN_FILENO);
//     for (int i = 0; i < *num_pipes; i++) 
//         close(pipes[i][0]); // Close read ends in parent after dup
// }

// int here_doc_final(t_token **final) {
//     int pc = 0;
//     int **pipes;

//     t_token *curr = *final;
//     while (curr) 
// 	{
//         if (curr->value == HEREDOC)
//             pc++;
//         curr = curr->next;
//     }
//     pipes = creat_pipes(&pc);
//     here_doc(final, &pc, pipes);
//     wait_children(&pc);

//     // Free the pipes memory
//     for (int i = 0; i < pc; i++) 
// 	{
//         free(pipes[i]);
//     }
//     free(pipes);
    
//     return 0;
// }
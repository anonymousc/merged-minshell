/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:03:40 by aessadik          #+#    #+#             */
/*   Updated: 2024/10/28 17:05:20 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char is_data_quotes(char c)
// {
// 	if(c == '\'')
// 		return '\'';
// 	else if(c == '"')
// 		return '"';
// 	return 0;
// }
// int count_qoutes(char *s , char quoted)
// {
// 	int wc = 0;
// 	while (s && *s)
// 	{
// 		if(*s == quoted)
// 			wc++;
// 		s++;
// 	}
// 	return wc;
// }
// char *d_qoutes_remover(char *s , char quoted)
// {
// 	int alloc = ft_strlen(s) - count_qoutes(s , quoted);
// 	char *replace = malloc(sizeof(char ) * (alloc + 1));
// 	int i = 0;
// 	int j = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != quoted)
// 		{
// 			replace[j] = s[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	replace[alloc] = 0;
// 	return(replace);
// }

// void if_s_or_d(t_token **final)
// {
// 	t_token *curr = *final;
// 	while (curr)
// 	{
// 		if(curr->value == WORD)
// 		{
// 			while(!is_quotes(*curr->data)  && (*curr->data))
// 			{
// 				curr->data++;
// 			}
// 			curr->data = d_qoutes_remover(curr->data , is_data_quotes(*curr->data));
// 		}
// 		curr = curr->next;
// 	}
// 	final = &curr;
// }

// typedef struct 
// {
//     char *str;
//     int in_dquote;
//     int in_squote;
// } quote_state;

char is_quote(char c) 
{
    if (c == '\'') return '\'';
    if (c == '"') return '"';
    return 0;
}

int count_chars_after_removal(char *s) 
{
    int count = 0;
    int in_dquote = 0;
    int in_squote = 0;
    
    while (s && *s) 
	{
        char q = is_quote(*s);
        if (q == '"' && !in_squote) 
            in_dquote = !in_dquote;
		else if (q == '\'' && !in_dquote) 
            in_squote = !in_squote;
		else 
            count++;
        s++;
    }
    return count;
}

char *remove_quotes(char *s) 
{    
    int len = count_chars_after_removal(s);
    char *result = malloc(sizeof(char) * (len + 1));
    int j = 0;
	int i = 0; 
    int in_dquote = 0;
    int in_squote = 0;
    
    while (s && s[i]) 
	{
        char q = is_quote(s[i]);
        if (q == '"' && !in_squote) 
            in_dquote = !in_dquote;
		else if (q == '\'' && !in_dquote) 
            in_squote = !in_squote;
		else 
            result[j++] = s[i];
		i++;
    }
    result[j] = '\0';
    return result;
}

void process_quotes(t_token **final) 
{
    t_token *curr = *final;
    
    while (curr) 
	{
        if (curr->value == WORD) 
		{
            char *processed = remove_quotes(curr->data);
            curr->data = processed;
        }
        curr = curr->next;
    }
}

void	free_stackhhh(t_execution **stack)
{
	t_execution	*tmp;

	tmp = *stack;
	while (tmp)
	{
		*stack = (*stack)->next;
		free(tmp);
		tmp = *stack;
	}
	stack = NULL;
}

int main (int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	// (void)envp;
	char *line;
	char **splitted_array;
	t_token  **final;
	t_execution **data;
	t_exec *exec = malloc (sizeof(t_exec));
	exec->env_orginal = envp;
	t_env *env = make_env(exec);
	exec->env = env;
	exec->env = env;
	line = NULL;
	char **env2 = env_to_arr(exec->env);
	while(1)
	{
		line = retline();
		final = (t_token  **)malloc(sizeof(t_token  *));
		data = (t_execution  **)malloc(sizeof(t_execution  *));
		if(!line)
			continue;
		splitted_array = split_to_lex(line);
		tokenization(splitted_array , final);
		
		sanitizer(final);
		expander_final(final ,env);
		process_quotes(final);
		if (check_syntax_extended(final))
			continue;
		free_spaces2(final);
		for_execute(final , data);
		execute_bins(data, env2);
		// print_tokens(*final);
		free_stackhhh(data);
		free_stack(final);
		free(final);
		free(data);
		fri_ol(splitted_array);
		free(line);
	}
}

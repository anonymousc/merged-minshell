/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:03:40 by aessadik          #+#    #+#             */
/*   Updated: 2024/11/28 20:55:55 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exit_status;

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
    char *processed;
    while (curr) 
	{
        if (curr->value == WORD) 
		{
            processed = remove_quotes(curr->data);
            curr->data = processed;
        }
        curr = curr->next;
    }
	// free(processed);
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

int parsing(t_token **final ,t_env *env, char **line)
{
	(void)env;
	tokenization(line , final);
	// ft_free11(line);
	sanitizer(final);
	expander_final(final , env);
	process_quotes(final);
	if (check_syntax_extended(final))
	{
		ft_free11(line);
		exit_status = 2;
		return 1;
	}
	free_spaces2(final);
	return 0;
}

int main (int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *line;
	char **splitted_array;
	t_token  **final = NULL;
	t_execution **data;
	t_env *env;
	line = NULL;
	env = NULL;
	while(1)
	{
		line = retline();
		final = (t_token  **)malloc(sizeof(t_token  *));
		data = (t_execution  **)malloc(sizeof(t_execution  *));
		if (!env)
			env = make_env(envp);
		if(!line)
			continue;
		splitted_array = split_to_lex(line);
		free(line);
		if(parsing(final , env, splitted_array))
		{
			// ft_free11(splitted_array);
			// free_stack(final);
			*final = NULL;
			continue;
		}
		for_execute(final , data);
		free_stack(final);
		(execute_bins(data, envp , &env));
		// print_tokens(*final);
		free_stackhhh(data);
		// free_stack(final);
		free(final);
		free(data);
		// ft_free11(splitted_array);
		// fri_ol(splitted_array);
		// free_lists();
	}
}

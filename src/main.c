/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:03:40 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/08 00:45:27 by aessadik         ###   ########.fr       */
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
		if(curr->value == HEREDOC && curr->next->next)
			curr = curr->next->next;
        else if (curr->value == WORD) 
		{
            processed = remove_quotes(curr->data);
			gc_add(0, processed , NULL);
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
void extra_sanitize(t_token **head)
{
    t_token* current = *head;
    t_token* tmp;

    while (current && current->next) 
	{
        if (current->value == WORD && !(*current->data)) 
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
			gc_add(0 , tmp , NULL);
		} 
		else 
            current = current->next;
    }
}

int parsing(t_token **final ,t_env **env ,t_execution **data)
{
	char *readline;
	char **line;

	line = NULL;
	readline = retline();
	if(!readline)
		return 1;
	line = split_to_lex(readline);
	tokenization(line , final);
	gc_add_double(0 , (void **)line, NULL);
	sanitizer(final);
	expander_final(final , *env);
	process_quotes(final);
	if (check_syntax_extended(final))
		return (exit_status = 2, 1);
	free_spaces2(final);
	for_execute(final , data , *env);
	return 0;
}

void execution(t_execution **data ,char **envp ,t_env **env)
{
	execute_bins(data, envp , env);
}

void exit_minishell(int exit_code)
{
	gc_free_all();
	exit(exit_code);
}

int main (int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_token  **final;
	t_execution **data;
	t_env *env;

	env = NULL;
	while(1)
	{
		final = (t_token  **)malloc(sizeof(t_token *));
		data = (t_execution  **)malloc(sizeof(t_execution  *));
		gc_add(MEMGRP_DEFAULT , final , NULL);
		gc_add(MEMGRP_DEFAULT, data, NULL);
		if (!env)
			env = make_env(envp);
		if(!data || parsing(final , &env, data) || !final)
			continue;
		my_export(NULL, &env, 0, 0);
		execution( data, envp, &env);
		
	}
}

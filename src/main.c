/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:03:40 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/01 22:27:23 by kali             ###   ########.fr       */
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
void extra_sanitize(t_token **fill_line)
{
		t_token *data;
	t_token *tmp;

	data = *fill_line;
    while (data && (data)->next) 
	{
        if ((data)->value == WORD && !(*data->data))
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

int parsing(t_token **final ,t_env **env, char **envp,t_execution **data)
{
	(void)env;
	char *readline;
	char **line;
	int fd_heredoc;

	line = NULL;
	if (!*env)
		*env = make_env(envp);
	readline = retline();
	if(!readline)
		return 1;
	line = split_to_lex(readline);
	free(readline);
	tokenization(line , final);
	sanitizer(final);
	// fd_heredoc = here_doc(final, *env);
	expander_final(final , *env);
	process_quotes(final);
	if (check_syntax_extended(final))
		return (ft_free11(line), exit_status = 2, 1);
	extra_sanitize(final);
	free_spaces2(final);
	for_execute(final , data, &fd_heredoc);
	return 0;
}

void execution(t_execution **data ,char **envp ,t_env *env)
{
	execute_bins(data, envp , &env);
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
		final = (t_token  **)malloc(sizeof(t_token  *));
		data = (t_execution  **)malloc(sizeof(t_execution  *));
		if(!data || parsing(final , &env, envp, data) || !final)
			continue;
		execution( data, envp, env);
		ft_combine_free(NULL, data, final);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:03:40 by aessadik          #+#    #+#             */
/*   Updated: 2024/10/01 19:59:15 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void assing_null(void *ref, ...)
{
	va_list refs;
	va_start(refs ,ref);
	ref = va_arg(refs , void *);
	va_end(refs);
}

int main (int ac, char **av, char **envp)
{
	(void)envp;
	(void)ac;
	(void)av;
	char *line;
	char **splitted_array;
	t_token  **final;
	t_env **env;
	// t_execution **data;

	line = NULL;
	env = NULL;
	env = fill_env(envp, env);
	while(1)
	{
		// data = (t_execution  **)malloc(sizeof(t_execution  *));
		final = (t_token  **)malloc(sizeof(t_token  *));
		// data = (t_execution  **)malloc(sizeof(t_execution  *));
		line = retline();
		if(!line)
			continue;
		splitted_array = split_to_lex(line);
		tokenization(splitted_array , final);
		
		sanitizer(final);
		if (check_syntax_extended(final))
			continue;
		here_doc(final);
		//expander(final); 
		// final_list_to_execute(final);
		// data = for_execute(final , data);//temprary function
		
		print_tokens(*final);
		free_stack(final);
		free(final);
		fri_ol(splitted_array);
		free(line);
	}
}

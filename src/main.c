/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:03:40 by aessadik          #+#    #+#             */
/*   Updated: 2024/09/24 18:45:01 by aessadik         ###   ########.fr       */
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

	line = NULL;
	env = NULL;
	env = fill_env(envp, env);
	while(1)
	{
		final = (t_token  **)malloc(sizeof(t_token  *));
		line = retline();
		if(!line)
			continue;
		splitted_array = split_to_lex(line);
		tokenization(splitted_array , final);
		
		sanitizer(final);
		if (check_syntax_extended(final))
			continue;
		//expander(final); 
		//final_list_to_execute(final);
		print_tokens(*final);
		free_stack(final);
		free(final);
		fri_ol(splitted_array);
		free(line);
	}
}

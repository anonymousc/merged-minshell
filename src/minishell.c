/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:23:23 by hatalhao          #+#    #+#             */
/*   Updated: 2024/12/07 21:52:00 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char  *retline()
{
		char *line;
		
		signal(SIGINT , sig_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		signal(SIGINT , sig_handler);
		add_history(line);
		if(!line)
			return (printf("exit\n"),exit_minishell(1) ,NULL);
		else if(line)
		{
			line = check_syntax(line);
			if(!line)
			{
				exit_status = 2;	
				free(line);
			}
		}
		return line;
}

int envp_size(char **envp)
{
	int i;
	
	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

void	lstadd_back(t_env **list, t_env *new)
{
	t_env	*head;

	head = *list;
	if (!head)
	{
		*list = new;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new;
	new->next = NULL;
}
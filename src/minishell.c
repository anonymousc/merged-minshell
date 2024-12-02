/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:23:23 by hatalhao          #+#    #+#             */
/*   Updated: 2024/12/01 01:01:46 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char  *retline(void)
{
		char *line;
		
		signal(SIGINT , sig_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("\e[32mminishell$ \e[0m");
		signal(SIGINT , sig_handler);
		add_history(line);
		if(!line)
			return (free(line) ,printf("exit\n") ,exit(1) ,NULL);
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
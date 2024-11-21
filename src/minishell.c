/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:23:23 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/12 02:03:41 by hatalhao         ###   ########.fr       */
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
				free(line);
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
// t_env *lst_new(char *data)
// {
// 	t_env *test;
// 	test = malloc(sizeof(t_env));
// 	test->env = data;
// 	test->next = NULL;
// 	return (test);
// }

// t_env	**fill_env(char **envp, t_env **env)
// {
// 	int 	i;
// 	int 	size;
// 	// t_env	*iter;

// 	i = -1;
// 	size = envp_size(envp);
// 	env = malloc(sizeof(t_env *));
// 	if(!env)
// 		return (free(env), NULL);
// 	*env = 0;
// 	// iter = *env;
// 	while(envp && ++i < size)
// 		lstadd_back(env, lst_new(envp[i]));
// 	return (env);
// }
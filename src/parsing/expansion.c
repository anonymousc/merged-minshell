/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:48:19 by kali              #+#    #+#             */
/*   Updated: 2024/10/05 14:59:02 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *expander(char *expansion, t_env *envp)
{
	char *expanded;
	char *to_compare;
	expansion = expansion + 1;
	while (envp)
	{
		int j = 0;
		while (envp->env[j] && envp->env[j] != '=')
			j++;
		to_compare = (char *)malloc(sizeof(char) * j + 1);
		if(!to_compare)
			return NULL;
		int k = 0;
		j = 0;
		while (envp->env[j] && envp->env[j] != '=')
		{
			to_compare[k] = envp->env[j];
			k++;
			j++;
		}
		to_compare[k] = 0;
		if(!strncmp(expansion , to_compare, strlen(to_compare)))
		{
			int i = 0;
			int tmp = j;
			while (envp->env[tmp])
			{
				tmp++;
				i++;
			}
			i -= 1;
			expanded = malloc(sizeof(char) * i + 1);
			if(!expanded)
				return NULL;
			i = 0;
			while (envp->env[j])
			{
				expanded[i] = envp->env[j + 1];
				j++;
				i++;
			}
			return (expanded);
		}
		free(to_compare);
		envp = envp->next;
	}
	return (NULL);
}

void expander_final(t_token **final ,t_env *env)
{
	t_token *curr;

	curr = *final;
	while (curr)
	{
		if(curr->data == '$' && (curr->data + 1 != ' ' || curr->data + 1 != '\''))
			curr->data = expander(curr->data , env);
		curr = curr->next;
	}
	*final  = curr;
}
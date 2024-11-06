/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:48:19 by kali              #+#    #+#             */
/*   Updated: 2024/10/28 18:58:25 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int check_in_db_or_sq(char *s)
{
	int dq = 0;
	int sq = 0;

	int i = 0;
	while (s[i])
	{
		if (s[i] == '"' && !sq)
			dq = 1;
		if (s[i] == '\'' && !dq)
			sq = 1;
		i++;
	}
	if (dq)
		return 2;
	if (sq)
		return 1;
	return 0;
}

char *find_env_variable2 (t_env *env, char *varname)
{
    while (env)
    {
        if (ft_strcmp(env->variable, varname) == 0)
        {
            return env->value;
        }
        env = env->next;
    }
    return NULL;
}

char *expander(char *expansion, t_env *envp)
{
	//$jhsd$USER jhjhk
	expansion = expansion + 1;
	
	if(!(find_env_variable2(envp , expansion)))
	{
		return (ft_strdup("\v"));
	}
	return (find_env_variable2(envp , expansion));
}

void expander_final(t_token **final ,t_env *env)
{
	t_token *curr;

	curr = *final;
	while (curr)
	{
			if(curr->value == WORD)
			{
				if (check_in_db_or_sq(curr->data) == 2 || !check_in_db_or_sq(curr->data))
				{
					curr->data = ft_strdup(remove_quotes(curr->data));
					int i = 0;
					while (curr->data[i])
					{
						if(curr->data[i] == '$')
						{
							char *tmp = expander(curr->data + i , env);
							*(curr->data + i) = '\0';
							if(*tmp)
							{
								tmp[ft_strlen(ft_strdup(tmp))] = '\0';
								curr->data = ft_strjoin(curr->data ,tmp);
							}
							else
								*(curr->data + i) = '\0';
						}
						i++;
					}
				}
			}
			curr = curr->next;
	}
	final  = &curr;
}

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
	expansion = expansion + 1;
	char *tmp = expansion;
	while (tmp && *tmp && (*tmp != '%' && *tmp != ' ' && *tmp != '@' && *tmp != '-' && *tmp != '+' && *tmp != '$'))
		tmp++;
	int l = tmp - expansion;
	char *to_expand = malloc (l + 1);
	strncpy(to_expand, expansion, l);
	to_expand[l] = '\0';
	if (!tmp)
		return (free(to_expand), expander(tmp, envp));
	if(!(find_env_variable2(envp , to_expand)) && tmp)
		return (free(to_expand) , ft_strdup("\v"));
	if (!tmp)
		return (find_env_variable2(envp , to_expand));
	else if (ft_strncmp(to_expand, "\v", 1))
		return (ft_strjoin(find_env_variable2(envp , to_expand), tmp));
	else
		return NULL;
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
							if(!curr->data[i + 1] || curr->data[i + 1] == '$')
								break;
							if(curr->data[i + 1] && curr->data[i + 1] == '?')
									printf("exitstatus");
							char *tmp = expander(curr->data + i , env);
							*(curr->data + i) = '\0';
							if(*tmp == '\v')
							{
								i++;
								continue;	
							}
							if(*tmp)
							{
								tmp[ft_strlen(ft_strdup(tmp))] = '\0';
								curr->data = ft_strjoin(curr->data ,tmp);
								free(tmp);
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
// void expander_final(t_token **final, t_env *env)
// {
//     t_token *curr;
//     char *expand_res = NULL;
    
//     curr = *final;
    
//     while (curr)
//     {
//         if (curr->value == WORD)
//         {
//             if (check_in_db_or_sq(curr->data) == 2 || !check_in_db_or_sq(curr->data))
//             {
//                 expand_res = NULL;
//                 curr->data = ft_strdup(remove_quotes(curr->data));
//                 char **segments = ft_split(curr->data, '%');
//                 int i = 0;
//                 while (segments[i])
//                 {
//                     int j = 0;
//                     int dollar_found = 0;
                    
//                     while (segments[i][j])
//                     {
//                         if (segments[i][j] == '$')
//                         {
//                             dollar_found = 1;
//                             char *tmp = expander(segments[i] + j, env);
//                             if (ft_strcmp(tmp, "\v"))
//                             {
//                                 expand_res = ft_strjoin2(expand_res, tmp);
//                             }
//                         }
//                         j++;
//                     }
                    
//                     if (!dollar_found)
//                     {
//                         expand_res = ft_strjoin2(expand_res, segments[i]);
//                     }
//                     i++;
//                 }
                
//                 if (!ft_strchr(expand_res, '\v'))
//                 {
//                     free(curr->data);
//                     curr->data = ft_strdup(expand_res);
//                     free(expand_res);
//                 }
                
//                 i = 0;
//                 while (segments[i])
//                 {
//                     free(segments[i]);
//                     i++;
//                 }
//                 free(segments);
//             }
//         }
//         curr = curr->next;
//     }

// }

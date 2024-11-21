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
    return (NULL);
}

char	*ft_strjoin2(char *s, char *s1)
{
	char	*p;
	char	*str;
	int		i;

	i = 0;
	if (!s && s1)
		return (ft_strdup(s1));
	else if (!s1 && s)
		return (ft_strdup(s));
	if (!s && !s1)
		return (NULL);
	p = (char *)malloc(ft_strlen(s) + ft_strlen(s1) + 1);
	if (!p)
		return (free(s), NULL);
	p[ft_strlen(s) + ft_strlen(s1)] = '\0';
	str = p;
	if (s)
	{
		while (s[i])
			*(p++) = s[i++];
	}
	i = 0;
	if (s1)
		while (s1[i])
			*(p++) = s1[i++];
	// free(s);
	// free(s1);
	return (str);
}


char	*before_dollar_word(char	*str)
{
	int i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i == 0)
		return (NULL);
	word = (char *)malloc(i + 1);
	word[i] = 0;
	strncpy(word,str, i);
	return (word);
}
char *expander(char *expansion, t_env *envp)
{
	//"rewrew$HOMErrrr$HOME"
	char *before_dollar = NULL;
	char *expanded_word;
	if (!expansion || *expansion != '$')
		return (NULL); 
	//printf ("expansion START with %c\n", *expansion);
	expansion = expansion + 1; // skips $
	char *tmp = expansion;
	while(tmp && *tmp && ft_isalnum(*tmp))
	while(tmp && *tmp && ft_isalnum(*tmp))
		tmp++;
	// in case it wasnt stooped by $
	//$HOMEffff%%%%%%%$HOME
	int l = tmp - expansion;
	char *to_expand = malloc (l + 1);
	strncpy(to_expand, expansion, l);
	to_expand[l] = '\0';
	//printf("to_expand == %s\n", to_expand);
	// going to expand
	expanded_word = find_env_variable2(envp , to_expand);
	if (*tmp && *tmp != '$')
	{
		before_dollar = before_dollar_word(tmp);
		while (*tmp && *tmp != '$')
			tmp++;
		//printf("beforedollar is %s\n", before_dollar);
		expanded_word = ft_strjoin2(expanded_word, before_dollar);
		//printf("newly expanded word %s\n", expanded_word);
	}
	//printf("expanded_word is %s\n", expanded_word);
	return (ft_strjoin2(expanded_word, expander(tmp, envp)));
}

void expander_final(t_token **final ,t_env *env)
{
	t_token *curr;
	char *tmp;

	curr = *final;
	while (curr)
	{
			if(curr->value == WORD)
			{
				if (check_in_db_or_sq(curr->data) == 2 || !check_in_db_or_sq(curr->data))
				{
					curr->data = ft_strdup(curr->data);
					int i = 0;
					while (curr->data[i])
					{
						if(curr->data[i] == '$')
						{
							if(!curr->data[i + 1] || curr->data[i + 1] == '$')
								break;
							if(curr->data[i + 1] && curr->data[i + 1] == '?')
									printf("exitstatus\n");
							char *tmp = expander(curr->data + i , env);
							if (tmp)
								printf("final expanded value is %s\n", tmp);
							else if (!tmp)
								return ;
							*(curr->data + i) = '\0';
							if(tmp && *tmp == '\v')
							{
								i++;
								continue;
							}
							if(*tmp)
							{
								tmp = ft_strjoin(curr->data ,tmp);
								curr->data = tmp;
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

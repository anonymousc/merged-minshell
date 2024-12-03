/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:48:19 by kali              #+#    #+#             */
/*   Updated: 2024/12/01 23:02:20 by kali             ###   ########.fr       */
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
	char *before_dollar;
	char *expanded_word;
	char *tmp;
	char *exit;

	before_dollar = NULL;
	if (!expansion || *expansion != '$')
		return (NULL);
	expansion = expansion + 1;
	tmp = expansion;
	if (tmp && *tmp == '?')
	{
		exit = ft_itoa(exit_status);
		before_dollar = before_dollar_word(tmp + 1);
		exit = ft_strjoin2(exit, before_dollar);
		return(ft_strjoin2(exit, expander(tmp + ft_strlen(before_dollar) + 1, envp)));
	}
	if (*tmp)
		tmp++;
	while(tmp && *tmp && ft_isalnum(*tmp))
		tmp++;
	int l = tmp - expansion;
	char *to_expand = malloc (l + 1);
	strncpy(to_expand, expansion, l);
	to_expand[l] = '\0';
	expanded_word = find_env_variable2(envp , to_expand);
	if (*tmp && *tmp != '$')
	{
		before_dollar = before_dollar_word(tmp);
		while (*tmp && *tmp != '$')
			tmp++;
		expanded_word = ft_strjoin2(expanded_word, before_dollar);
	}
	return (ft_strjoin2(expanded_word, expander(tmp, envp)));
}

t_token *make_token_list(char **split)
{
	t_token *head = NULL;
	t_token *new_token = NULL;
	t_token *curr = NULL;

	int i = 0;
	while (split && split[i])
	{
		new_token = malloc (sizeof(t_token));
		new_token->data = ft_strdup(split[i]);
		new_token->value = WORD;
		new_token->next = NULL;
		if (!head)
			head = new_token;
		else
			curr->next = new_token;	
		curr = new_token;
		i++;
	}
	return head;
}
t_token *make_token_list2(char **split)
{
	t_token *head = NULL;
	t_token *new_token = NULL;
	t_token *curr = NULL;

	int i = 0;
	while (split && split[i])
	{
		new_token = malloc (sizeof(t_token));
		new_token->data = ft_strdup(split[i]);
		new_token->value = get_token(split[i]);
		new_token->next = NULL;
		if (!head)
			head = new_token;
		else
			curr->next = new_token;	
		curr = new_token;
		i++;
	}
	return head;
}
char **token_to_char(t_token *list)
{
	char **split = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	int i = 0;
	while (list)
	{
		split[i] = list->data;
		i++;
		list = list->next;
	}
	split[i] = NULL;
	return split;
}
void expander_final(t_token **final ,t_env *env)
{
	t_token *curr;
	char *tmp;
	t_token *prev;

	curr = *final;
	while (curr)
	{
		if(curr->next)
			prev = curr;
		if(curr->value == HEREDOC)
			curr = curr->next->next;
		else if(curr->value == WORD)
		{
			if (check_in_db_or_sq(curr->data) == 2)
			{
				curr->data = ft_strdup(curr->data);
				int i = 0;
				while (curr->data[i])
				{
					if(curr->data[i] == '$')
					{
						tmp = expander(curr->data + i , env);
						*(curr->data + i) = '\0';
						if(tmp && *tmp == '\v')
						{
							i++;
							continue;
						}
						if(tmp && *tmp)
						{
							tmp = ft_strjoin(curr->data ,tmp);
							free(curr->data);
							curr->data = tmp; 
						}
						else
							*(curr->data + i) = '\0';
					}
					i++;
				}
			}
			if(!check_in_db_or_sq(curr->data))
			{
				curr->data = ft_strdup(curr->data);
				int i = 0;
				while (curr->data[i])
				{
					if(curr->data[i] == '$')
					{
						tmp = expander(curr->data + i , env);
						*(curr->data + i) = '\0';
						if(tmp && *tmp)
						{
							tmp = ft_strjoin(curr->data ,tmp);
							if (ft_strchr(tmp, ' '))
							{
								
								char **split = ft_split(tmp, ' ');
								char **next = token_to_char(curr->next);
								if (*final == curr)
								{
									*final = make_token_list(split);
									curr = *final;
									while (curr && curr->next)
										curr = curr->next;
									curr->next = make_token_list2(next);
								}
								else
								{
									curr = make_token_list(split);
									t_token *last = ft_lstlast(curr);
									t_token *copy2 = *final;
									while (copy2 && copy2->next && copy2->next != curr)
										copy2 = copy2->next;
									prev->next = curr;
									t_token *copy = *final;
									while (copy)
										copy = copy->next;
									copy = make_token_list2(next);
									last->next = copy;	
								}
							}
							else
								curr->data = tmp;
						}
						else
							*(curr->data + i) = '\0';
					}
					i++;
				}
			}
		}
		if(curr)
			curr = curr->next;
	}
	extra_sanitize(final);
}
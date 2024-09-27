/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 03:44:27 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/24 10:51:28 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	word_count(char const *s)
{
	size_t		counter;
	int			in_word;
	char const	*p;

	if (s == NULL)
		return (0);
	counter = 0;
	in_word = 0;
	p = s;
	while (*p)
	{
		if (is_space(*p))
			in_word = 0;
		else if (in_word == 0)
		{
			counter++;
			in_word = 1;
		}
		p++;
	}
	return (counter);
}

char **fri_ol(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	**str_all_fill(char **str, char const *s)
{
	const char	*start;
	int			i;
	int			len;

	i = 0;
	while (*s)
	{
		if (!is_space(*s))
		{
			start = s;
			while (*s && !is_space(*s))
				s++;
			len = s - start;
			str[i] = (char *)malloc((len + 1) * sizeof(char));
			if (!str[i])
				return (fri_ol(str));
			ft_memcpy(str[i], start, len);
			str[i][len] = '\0';
			i++;
		}
		else
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s)
{
	char		**str;

	if (!s)
		return (0);
	str = malloc((word_count(s) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (str_all_fill(str, s));
}

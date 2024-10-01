/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:09:31 by hatalhao          #+#    #+#             */
/*   Updated: 2023/11/05 19:29:05 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;

	str = (unsigned char *) s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return ((char *)(str + i));
		i--;
	}
	return (0);
}

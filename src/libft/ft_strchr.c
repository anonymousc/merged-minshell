/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:41:47 by hatalhao          #+#    #+#             */
/*   Updated: 2023/11/05 19:25:13 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	size_t			len;
	unsigned char	chr;

	chr = c;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == chr)
			return ((char *)(s + i));
		else
			i++;
	}
	return (0);
}

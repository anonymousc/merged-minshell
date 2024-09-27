/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:19:50 by hatalhao          #+#    #+#             */
/*   Updated: 2023/11/03 17:22:16 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	chr;

	str = (unsigned char *) s;
	chr = c;
	i = 0;
	while (i < n)
	{
		if (str[i] != chr)
			i++;
		else
			return (str + i);
	}
	return (NULL);
}

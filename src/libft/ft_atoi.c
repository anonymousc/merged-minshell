/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:24:11 by hatalhao          #+#    #+#             */
/*   Updated: 2024/04/19 16:37:31 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char const *nptr)
{
	int					i;
	int					s;
	unsigned long long	r;

	i = 0;
	s = 1;
	r = 0;
	while (nptr && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr && nptr[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (nptr && nptr[i] == '+')
		i++;
	while (nptr && nptr[i] >= '0' && nptr[i] <= '9')
		r = r * 10 + nptr[i++] - '0';
	if ((r > INT_MAX) || (((int)r * s) < INT_MIN))
	{
		write(2, "Error\n", 6);
		exit (0);
	}
	return ((int)(r * s));
}

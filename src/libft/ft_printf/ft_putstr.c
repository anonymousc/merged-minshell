/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:31 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/21 11:14:18 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(int fd, char *str, int *c)
{
	if (!str)
	{
		ft_putstr(fd, "(null)", c);
		return ;
	}
	while (*str)
	{
		ft_putchar(fd, *str, c);
		str++;
	}
}

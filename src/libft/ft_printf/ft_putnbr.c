/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/21 11:16:51 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int fd, long nb, int *c)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar(fd, '-', c);
	}
	if (nb >= 10)
		ft_putnbr(fd, nb / 10, c);
	ft_putchar(fd, nb % 10 + '0', c);
}
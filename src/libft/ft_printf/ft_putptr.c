/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:19 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/21 11:17:02 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr(int fd, unsigned long l, int *c)
{
	ft_putstr(fd, "0x", c);
	if (l >= 16)
		ft_puthex(fd, l / 16, c);
	ft_putchar(fd, "0123456789abcdef"[l % 16], c);
}

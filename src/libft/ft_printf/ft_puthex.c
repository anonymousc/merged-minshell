/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:03 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/21 11:16:47 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(int fd, unsigned long l, int *c)
{
	if (l >= 16)
		ft_puthex(fd, l / 16, c);
	ft_putchar(fd, "0123456789abcdef"[l % 16], c);
}
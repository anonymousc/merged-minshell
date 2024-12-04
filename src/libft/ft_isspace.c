/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:17:25 by aessadik          #+#    #+#             */
/*   Updated: 2024/10/01 20:05:22 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


int is_space(char c)
{
	return (((c >= 9 && c <= 13) || c == 32));
}

char *is_space_veta(char s)
{
	if(s == ' ')
		return (" ");
	if(s == '\t')
		return ("\t");
	if(s == '\n')
		return ("\n");
	if(s == '\f')
		return ("\f");
	if(s == '\r')
		return ("\r");
	return NULL;
}
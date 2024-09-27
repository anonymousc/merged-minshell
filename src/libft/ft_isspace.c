/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:17:25 by aessadik          #+#    #+#             */
/*   Updated: 2024/08/21 16:18:40 by aessadik         ###   ########.fr       */
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
	else if(s == '\t')
		return ("\t");
	else if(s == '\a')
		return ("\a");
	else if(s == '\f')
		return("\f");
	else if(s == '\r')
		return ("\r");
	else if(s == '\n')
		return ("\n");
	return NULL;
}
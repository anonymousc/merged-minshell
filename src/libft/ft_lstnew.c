/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 03:36:37 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/24 18:22:05 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_token  *ft_lstnew(char *content , Token t)
{
	t_token   *list;

	list = (t_token  *) malloc (sizeof(t_token ));
	if (!list)
		return (NULL);
	list->data = content;
	list->value = t;
	list->next = NULL;
	return (list);
}

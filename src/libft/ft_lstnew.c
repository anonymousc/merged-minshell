/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 03:36:37 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 19:56:11 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_token	*ft_lstnew(char *content, Token t)
{	t_token  *list;

	list = (t_token *) malloc (sizeof(t_token));
	if (!list)
		return (NULL);
	list->value = t;
	list->data = content;
	list->next = NULL;
	return (list);
}

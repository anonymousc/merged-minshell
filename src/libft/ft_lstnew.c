/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 03:36:37 by hatalhao          #+#    #+#             */
/*   Updated: 2024/12/08 00:38:23 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/minishell.h"

t_token	*ft_lstnew(char *content, Token t)
{	
	t_token  *list;

	list = (t_token *) malloc (sizeof(t_token));
	list->value = t;
	list->data = content;
	list->next = NULL;
	return (list);
}

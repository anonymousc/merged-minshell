/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 03:36:43 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/24 14:55:21 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_token 	*ft_lstlast(t_token  *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

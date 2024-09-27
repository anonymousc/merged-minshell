/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 07:37:41 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/24 14:55:21 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_token  **lst)
{
	t_token 	*tmp;
	
	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		ft_lstdelone(&tmp);
		*lst = (*lst)->next;
	}
	free(*lst);
}

// int main()
// {
// 	t_list	*i;
// 	t_list	*k;
	
// 	t_list	*a;
// 	t_list	*b;
// 	t_list	*c;
// 	t_list	*d;

// 	a = (t_list *) malloc (sizeof(t_list));
// 	b = (t_list *) malloc (sizeof(t_list));
// 	c = (t_list *) malloc (sizeof(t_list));
// 	d = (t_list *) malloc (sizeof(t_list));

// 	a->content = malloc (sizeof(int));
// 	b->content = malloc (sizeof(int));
// 	c->content = malloc (sizeof(int));
// 	d->content = malloc (sizeof(int));

// 	a->next = b;
// 	b->next = c;
// 	c->next = d;
// 	d->next = NULL;

// 	a ->content = 1;
// 	b ->content = 5;
// 	c ->content = 9;
// 	d ->content = 13;

// 	i = a;
// 	while (i)
// 	{
// 		printf("%d\n", i->content);
// 		i = i->next;
// 	}

// 	printf("--- Before ---\n");

// 	k = a;
// 	ft_lstclear(&a);

// 	printf("--- AFTER ---\n");
// 	while (k)
// 	{
// 		printf("%d\n", k->content);
// 		k = k->next;
// 	}
// }
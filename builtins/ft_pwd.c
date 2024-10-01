/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:31:08 by aessadik          #+#    #+#             */
/*   Updated: 2024/10/01 04:28:31 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void ft_exit(t_final *list)
{
	if((long long)ft_atoi(list->data) < INT_MAX)
		exit(ft_atoi(av[1]));
	if(list->next->data)
	{
		printf("too many arguements\n");
		return ;
	}
}

int main(int ac , char **av)
{
	ft_exit(av);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:17:52 by kali              #+#    #+#             */
/*   Updated: 2024/11/25 23:17:53 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void my_exit(t_execution *list)
{
	printf ("hhhh\n");
	if((long long)ft_atoi(list->cmd[1]) < INT_MAX)
	{
		printf("exit\n");
		exit(ft_atoi(list->cmd[1]));
	}
	if(list->cmd[2])
	{
		printf("too many arguements\n");
		return ;
	}
}

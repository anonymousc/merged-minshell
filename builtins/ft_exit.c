/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:03:12 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/07 00:55:09 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void my_exit(t_execution *list)
{
	if((long long)ft_atoi(list->cmd[1]) < INT_MAX)
	{
		printf("exit\n");
		// exit(ft_atoi(list->cmd[1]));
		exit_minishell(ft_atoi(list->cmd[1]));
	}
	if(list->cmd[2])
	{
		printf("too many arguements\n");
		return ;
	}
}

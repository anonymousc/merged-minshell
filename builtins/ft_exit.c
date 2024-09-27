/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:31:08 by aessadik          #+#    #+#             */
/*   Updated: 2024/09/12 03:38:51 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_integer(long nb)
{
	return (nb >= INT_MIN && nb <= INT_MAX);
}

void	ft_exit(t_final *list)
{
	unsigned char	status;
	long			arg;

	arg = ft_atoi(list->data);
	status = 0;
	if(list->next->data)
	{
		ft_printf(2, "too many arguements\n");
		//  EXIT_STATUS_ENV = 1;
		return ;
	}
	if(is_integer(arg))
		status = arg;
	else
		status = 2;
	exit(status);
}

// int main(int ac , char **av)
// {
// 	ft_exit(av);
// }

int main()
{
	long nb = -4864646849874;
	unsigned char c = nb;
	printf("c == %d\n", c);
	exit(c);
}

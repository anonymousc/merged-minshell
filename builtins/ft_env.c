/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:02:59 by aessadik          #+#    #+#             */
/*   Updated: 2024/10/01 04:27:00 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(int ac, char **av)
{
	if (ac > 2)
		ft_printf(2, "minishell: cd: too many arguments\n");
	else if (ac == 2)
	{
		if(chdir(av[1]) && av[1][0] != '-')
		{
			perror(av[1]);
		}
	}
	else if (!av[1] || !ft_strcmp("~", av[1]))
	{
		if (getenv("HOME"))
			chdir(getenv("HOME"));
		else
			ft_printf(2, "minishell: cd: HOME not set\n");
	}
	else if(!strcmp("-", av[1]))
	{
		if (getenv("OLDPWD"))
		{
			chdir(getenv("OLDPWD"));	
			getenv("OLDPWD");
		}
		else
			ft_printf(2, "minishell: cd: OLDPWD not set\n");
	}
}

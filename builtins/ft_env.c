/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:57:56 by aessadik          #+#    #+#             */
/*   Updated: 2024/08/31 17:45:43 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_env(t_env **env)
{
	while (*env && (*env)->next)
	{
		printf("%s\n", (*env)->env);
		*env = (*env)->next;
	}
}
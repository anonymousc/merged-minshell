/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:03:12 by aessadik          #+#    #+#             */
/*   Updated: 2024/08/26 16:05:31 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char	*s;

	s = malloc(sizeof(char) * (PATH_MAX + 1));
	if (!s)
		return ;
	if (!getcwd(s, PATH_MAX))
		return (perror(strerror(errno)), free(s));
	printf("%s\n", getcwd(s, PATH_MAX));
	free(s);
}

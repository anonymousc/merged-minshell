/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:07:35 by aessadik          #+#    #+#             */
/*   Updated: 2024/11/28 20:59:44 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void sig_handler(int test)
{
	(void)test;
	printf("\n");
	rl_on_new_line ();
	rl_replace_line ("", 0);
	rl_redisplay();
	exit_status = 130;
	return ;
}

void sig_handler1(int test)
{
	(void)test;
	exit_status = 131;
	printf("\n");
	return ;
}
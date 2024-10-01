/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:07:35 by aessadik          #+#    #+#             */
/*   Updated: 2024/10/01 04:25:14 by kali             ###   ########.fr       */
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
	return ;
}

void sig_handler1(int test)
{
	(void)test;
	// rl_replace_line ("", 0);
	// rl_on_new_line ();
	signal(SIGQUIT, SIG_IGN);
	// rl_redisplay();
	// return ;
}
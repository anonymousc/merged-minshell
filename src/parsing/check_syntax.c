/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:14:18 by aessadik          #+#    #+#             */
/*   Updated: 2024/09/04 11:14:35 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *check_quotes(char *s)
{
	t_syntax syntax;

	syntax.iter = 0;
	int sq = 0;
	int dq = 0;
	while(s[syntax.iter])
	{
		if(s[syntax.iter] == '\'' && !dq)
			sq = !sq;
		if(s[syntax.iter] == '\"' && !sq)
			dq = !dq;
		syntax.iter++;
	}
	if(dq || sq)
		return (printf("minishell: Unclosed Quotes\n"), NULL);
	return(s);
}

char *check_syntax(char *s)
{
	if(!check_quotes(s))
		return (free(s), NULL);
	return (s);
}
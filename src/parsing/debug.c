/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:24:30 by aessadik          #+#    #+#             */
/*   Updated: 2024/09/24 18:34:15 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void print_tokens(t_token *list)
{
	int wc;
	
	wc = 0;

	while (list)
	{
		if(list->value == PIPE)
			printf("token type : PIPE its_data == %s\n" , list->data);
		if(list->value == REDIRECTION_IN)
			printf("token type : REDIRECTOIN_IN its_data == %s\n" , list->data);
		if(list->value == REDIRECTION_OUT)
			printf("token type : REDIRECTOIN_OUT its_data == %s\n" , list->data);
		if(list->value == APPEND)
			printf("token type : APPEND its_data == %s\n" , list->data);
		if(list->value == HEREDOC)
		{
			wc++;
			if(wc == 17)
			{
				printf("SYNTAX_ERROR(minishell: maximum here-document count exceeded)\n");
				exit (2);
			}
			printf("token type : HEREDOC its_data == %s\n" , list->data);
		}
		if(list->value == WORD)
			printf("token type : WORD its_data == %s\n" , list->data);
		if(list->value == WHITESPACE)
			printf("token type : WHITESPACE its_data == %d\n" ,  (*list->data));
		list = list->next;
	}
}
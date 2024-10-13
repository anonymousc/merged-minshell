/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:24:30 by aessadik          #+#    #+#             */
/*   Updated: 2024/10/10 15:43:08 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void print_tokens(t_token *list)
{

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
			printf("token type : HEREDOC its_data == %s\n" , list->data);
		if(list->value == WORD)
			printf("token type : WORD its_data == %s\n" , list->data);
		if(list->value == WHITESPACE)
			printf("token type : WHITESPACE its_data == %d\n" ,  (*list->data));
		list = list->next;
	}
}
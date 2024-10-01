#include "libft.h"

void ft_lstdelone(t_token **lst)
{
	if (!lst || !*lst)
		return ;
	free ((*lst)->data);
	free (*lst);
}
void	free_stack(t_token **stack)
{
	t_token	*tmp;

	tmp = *stack;
	while (tmp)
	{
		*stack = (*stack)->next;
		free(tmp);
		tmp = *stack;
	}
	stack = NULL;
}

void	free_env(t_env **stack)
{
	t_env	*tmp;

	tmp = *stack;
	while (tmp)
	{
		*stack = (*stack)->next;
		free(tmp);
		tmp = *stack;
	}
	stack = NULL;
}
#include "../includes/minishell.h"

void	rotate(t_env **stack)
{

	if ((*stack) && (*stack)->next)
	{
		(*stack) = (*stack)->next;
	}
}

t_env **unset_var(t_execution **exec, char *s, t_env **env) 
{
    (void)exec;

    // t_env *to_remove = NULL;
    if (*env && strcmp((*env)->variable, s) == 0)
	{
        rotate(env);
    }
    t_env *curr = *env;
    while (curr && curr->next) 
	{
        if (strcmp(curr->next->variable, s) == 0) 
		{
            // to_remove = curr->next;
            curr->next = curr->next->next;
            // free(to_remove);
        }
		else 
             curr = curr->next;
    }
    return env;
    // curr = *env;
}
int my_unset(t_execution **exec, t_env **env)
{
	int i = 1;
	while ((*exec)->cmd[i])
	{
		env = unset_var(exec, (*exec)->cmd[i], env);
        i++;
	}
	return 0;
}
#include "builtins.h"

void unset_var(t_execution **exec, char *s, t_env *env) 
{
    (void)exec;
    t_env *curr = env;
    t_env *to_remove = NULL;

    while (curr && curr->next) 
	{
        if (strcmp(curr->next->variable, s) == 0) 
		{
            to_remove = curr->next;
            curr->next = curr->next->next;
            free(to_remove);
        } 
		else 
		{
            curr = curr->next;
        }
    }

    curr = env;
    if (curr && strcmp(curr->variable, s) == 0) 
	{
        to_remove = curr;
        env = curr->next;
    	free(to_remove);
    }
}

int my_unset(t_execution **exec, t_env *env)
{
	int i = 1;
	while ((*exec)->cmd[i])
	{
		unset_var(exec, (*exec)->cmd[i], env);
		i++;
	}
	return 0;
}

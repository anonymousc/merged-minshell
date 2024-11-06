#include "builtins.h"

void unset_var(t_exec **exec, char *s) 
{
    t_env *curr = (*exec)->env;
    t_env *to_remove = NULL;

    while (curr && curr->next) 
	{
        if (strncmp(curr->next->variable, s, strlen(s)) == 0) 
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

    curr = (*exec)->env;
    if (curr && strncmp(curr->variable, s, strlen(s)) == 0) 
	{
        to_remove = curr;
        (*exec)->env = curr->next;
    	free(to_remove);
    }
}

int my_unset(t_exec **exec)
{
	int i = 1;
	while ((*exec)->av[i])
	{
		unset_var(exec, (*exec)->av[i]);
		i++;
	}
	return 0;
}

// int main(int ac ,char **av , char **envp)
// {
// 	t_exec *exec = malloc(sizeof(t_exec));
// 	exec->env_orginal = envp;
// 	t_env *env = make_env(exec);
// 	exec->env = env;
// 	exec->av = av;
// 	exec->ac = ac;
// 	int i = 0;
// 	my_unset(&exec);
// 	t_env *current = exec->env;
// 	my_env(&current);
// 	free_env(&current);
// }
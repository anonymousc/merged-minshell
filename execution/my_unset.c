#include "builtins.h"

void my_unset(t_exec **exec, char *s) 
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

int main(int ac ,char **av , char **envp)
{
	t_exec *exec = malloc(sizeof(t_exec));
	exec->env_orginal = envp;
	t_env *env = make_env(exec);
	exec->env = env;
	exec->av = av;
	exec->ac = ac;
	int i = 0;
	while(ac > ++i)
	{
		my_unset(&exec , av[i]);
		i++;
	}
	t_env *current = exec->env;
	while (current)
	{
		printf ("%s=%s\n", current->variable, current->value);
		current = current->next;
	}
}
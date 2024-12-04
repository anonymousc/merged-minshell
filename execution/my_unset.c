#include "../includes/minishell.h"


// t_env **unset_var(t_execution **exec, char *s, t_env **env) 
// {
//     (void)exec;

//     t_env *curr = *env;

//     if(!s)
//         return env;
//     if (!strcmp((*env)->variable, (*exec)->cmd[1]))
//     {
//             printf("hhhh\n");
//             (*env) = (*env)->next;
//     }
//     while (curr && curr->next) 
// 	{
//         if (strcmp(curr->next->variable, s) == 0) 
// 		{
//             // to_remove = curr->next;
//             curr->next = curr->next->next;
//             // free(to_remove);
//         }
// 		else 
//              curr = curr->next;
//     }
//     return env;
// }
// int my_unset(t_execution **exec, t_env **env)
// {
// 	int i = 1;
//     if(exec)
//     {
// 	    while ((*exec)->cmd[i])
// 	    {
//             env = unset_var(exec, (*exec)->cmd[i], env);
//             i++;
//         }
//         // env = unset_var(exec, NULL, env);
//     }
// 	return 0;
// }


t_env **unset_var(t_execution **exec, char *s, t_env **env) 
{
    (void)exec;

    t_env *curr = *env;
    t_env *tmp;

    if (curr && !strcmp(curr->variable, s))
    {
        tmp = curr;
        curr = curr->next;
        *env = curr;
        free(tmp->variable);
        free(tmp->value);
        free(tmp);
    }
    else
    {
        while (curr && curr->next) 
	    {
            if (strcmp(curr->next->variable, s) == 0) 
	    	{
                tmp = curr->next;
                curr->next = curr->next->next;
                free(tmp->variable);
                free(tmp->value);
                free(tmp);
            }
            curr = curr->next;
        }
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
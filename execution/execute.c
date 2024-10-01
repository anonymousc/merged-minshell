#include "builtins.h"

int execute_builtins(t_execution *exec)
{
	int ret;
	if (strncmp(exec->av[0], "echo", 5) == 0)
		ret = my_echo(exec->ac, exec->av);
	else if (strncmp (exec->av[0], "cd", 3) == 0)
		ret = my_cd(exec);
	else if (strncmp (exec->av[0], "pwd", 4) == 0)
		ret = my_pwd();
	else if (strncmp (exec->av[0] , "env", 4) == 0)
		ret = my_env(exec->env);
	else if (strncmp(exec->av[0] , "export", 7) == 0)
		ret = my_export(exec);
	else 
		return 1;
}
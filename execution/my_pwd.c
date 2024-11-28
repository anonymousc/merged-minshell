#include "../includes/minishell.h"

int	my_pwd(int fd, t_env *env)
{
	char	*s;

	s = malloc(sizeof(char) * (PATH_MAX + 1));
	if (!s)
		return 1;
	if (!getcwd(s, PATH_MAX))
        return (ft_printf(fd, "%s\n", find_env_variable2(env , "PWD")) ,free(s) , 1);
    return (ft_printf(fd, "%s\n", getcwd(s, PATH_MAX)) ,free(s) ,0);
}
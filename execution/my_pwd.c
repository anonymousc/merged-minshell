#include "builtins.h"

int my_pwd(int fd, t_env *env)
{
    char path[1024];

    ft_printf(fd,"test\n");
    if (getcwd(path, sizeof (path)))
        ft_printf (fd ,"%s\n", path);
    else
        ft_printf (fd, "%s\n",find_env_variable2(env, "PWD"));
    return 0;
}

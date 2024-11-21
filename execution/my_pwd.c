#include "builtins.h"

int my_pwd(int fd)
{
    char path[1024];

    ft_printf(fd,"test\n");
    if (getcwd(path, sizeof (path)))
        ft_printf (fd ,"%s\n", path);
    else
        perror ("error\n");
    return 0;
}

// int main ()
// {
//     my_pwd();
// }
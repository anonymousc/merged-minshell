#include "builtins.h"

int my_pwd()
{
    char path[1024];

    if (getcwd(path, sizeof (path)))
        printf ("%s\n", path);
    else
        perror ("error\n");
    return 0;
}

// int main ()
// {
//     my_pwd();
// }
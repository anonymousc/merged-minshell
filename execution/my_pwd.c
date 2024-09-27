#include "builtins.h"

void my_pwd()
{
    char path[1024];

    if (getcwd(path, sizeof (path)))
        printf ("%s", path);
    else
        perror ("error\n");
}

// int main ()
// {
//     my_pwd();
// }
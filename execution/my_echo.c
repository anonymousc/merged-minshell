#include "builtins.h"

bool check_newline(int ac, char **av, int *start_i)
{
    bool new_line = true;
    *start_i = 1;

    while (*start_i < ac && av[*start_i][0] == '-') 
    {
        int i = 1;
        while (av[*start_i][i] == 'n') 
        {
            new_line = false;
            i++;
        }
        if (av[*start_i][i] != '\0') 
        {
            break;
        }
        (*start_i)++;
    }
    return new_line;
}

int my_echo (int ac, char **av)
{
    int start_i;
    bool new_line;

    new_line = check_newline(ac, av, &start_i);
    while (start_i < ac)
    {
        printf ("%s", av[start_i]);
        if (start_i < ac - 1)
            printf(" ");
        start_i++;
    }

    if (new_line)
        printf ("\n");
    return 0;
}

// int main (int ac , char **av)
// {
//     my_echo(ac, av);
// }
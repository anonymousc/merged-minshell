#include "../includes/minishell.h"

bool check_newline( int ac, char **av, int *start_i)
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

int my_echo (int fd ,int ac, char **av)
{
    int start_i;
    bool new_line;

    if(!av[1])
    {
        ft_printf(fd , "\n");
        return false;
    }
    new_line = check_newline(ac, av, &start_i);
    while (start_i < ac)
    {
        ft_printf (fd, "%s", av[start_i]);
        if (start_i < ac - 1)
            ft_printf(fd, " ");
        start_i++;
    }

    if (new_line)
        ft_printf (fd, "\n");
    return 0;
}

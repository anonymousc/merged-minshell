#include "../../includes/minishell.h"

char *randgen(char *s)
{
    char *pathname = "/tmp/";
    char *suffix = "\v";

    s = ft_strjoin(pathname, suffix);
    
    return s;
}

int file_to_write_on(char **filename)
{
    char *path = randgen(*filename);
    int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
    *filename = path;
    return fd;
}

void delete_file(char *filename)
{
    unlink(filename);
}
 
void here_doc_child(t_token *final , int *fd1)
{
    t_token *curr = final;
    int fd;
    char *line;
    char *filename = NULL;
    fd = 0;
    if (curr && curr->value == HEREDOC)
    {
        fd = file_to_write_on(&filename);
        curr = free_spaces(curr->next);
        char *delim = curr->data;
        while (1)   
        {
            signal(SIGINT, sig_handler1);
            line = readline(">");
            if (!line)
            {
                ft_printf(2, "warning: here-doc delimited by end-of-file\n");
                break;
            }
            if (!ft_strncmp(delim, line, ft_strlen(delim) + 1))
            {
                free(line);
                break;
            }
            if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
                ft_printf(2, "Error: Unable to write to heredoc file\n");
            free(line);
            // signal(SIGINT, sig_handler1);
        }
        close(fd);
        fd = open(filename, O_RDONLY);
        delete_file(filename);
    }
	*fd1 = fd;
}

int here_doc(t_token **final)
{
    int hc = 0;
    t_token *curr = *final;
    t_token *herecount = curr;
	int fd;

    fd = 0;
    while (herecount)
    {
        if (herecount->value == HEREDOC)
            hc++;
        if (hc >= 17)
        {
            ft_printf(2, "minishell: maximum here-document count exceeded\n");
            exit(2);
        }
        herecount = herecount->next;
    }
    if (curr->value == HEREDOC)
    {
        free_spaces(curr->next);
        here_doc_child(curr , &fd);
    }
	return (fd);
}

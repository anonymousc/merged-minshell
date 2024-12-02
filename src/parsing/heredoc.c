#include "../../includes/minishell.h"

char *namegen()
{
    int fd = open("/dev/random" , O_RDONLY);
    int i = 0;
    char *file = malloc(11);
    char *buf = malloc (1);
    int j = 0;
    while (i < 10)
    {
        read(fd, buf, 1);
        if (__isascii(*buf))
        {
            file[j] = *buf;
            j++;
        }
        i++;
    }
    file[j] = '\0';
    free(buf);
    return file;
}

char *randgen(char *s)
{
    char *pathname = "/tmp/";

    s = ft_strjoin(pathname, namegen());
    
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
 
void here_doc_child(t_token *final , int *fd1, t_env *env)
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
        int check = check_in_db_or_sq(delim);
        while (1)   
        {
            signal(SIGINT, sig_handler1);
            line = readline(">");
            if (!check && line[0] == '$')
            {
                line = expander(line, env);
                if(!line)
                    line = ft_strdup("");
            }
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
            printf ("kiktb f %d\n",fd);
            if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
                ft_printf(2, "Error: Unable to write to heredoc file\n");
            free(line);
        }
        close(fd);
        fd = open(filename, O_RDONLY);
        delete_file(filename);
    }
	*fd1 = fd;
}

int here_doc(t_token **final, t_env *env)
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
        here_doc_child(curr , &fd, env);
    }
	return (fd);
}

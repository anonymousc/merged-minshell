#include "../../includes/minishell.h"

// char *randgen(char *s)
// {
// 	char *pathname = "/tmp/.";
// 	static char *add;
// 	add = ft_strdup(" ");
// 	s = ft_strjoin(pathname , add);
// 	(*add)++;
// 	free(add);
// 	return (s);
// }

// int file_to_write_on(char *filename)
// {
// 	int fd = open (randgen(filename) , O_RDWR  | O_CREAT);
// 	return (fd);
// }

// void delete_file(char *filename)
// {
// 	unlink(filename);
// }

// void here_doc_child(t_token **final)
// {
// 	t_token *curr = *final;
// 	int fd;
// 	char *line;
// 	char *filename;

// 	fd = 0;
// 	filename = NULL;
// 	if (curr && curr->value == HEREDOC)
// 	{
// 		fd = file_to_write_on(filename);
// 		dup2(fd , STDOUT_FILENO);
// 		close (STDOUT_FILENO);
// 		curr = free_spaces(curr->next);
// 		char *delim = curr->data;
// 		while (1)
// 		{
// 			line = readline(">");
// 			if (write(fd, "test\n", 5) == -1)
// 			{
// 				ft_printf(2, "fd is %d\n", fd);
// 				ft_printf(2, "warning here_doc delimited\n");
// 			}
// 			if(!line)
// 				ft_printf(2, "warning here_doc delimited\n");
// 			if (!ft_strncmp(delim , line, ft_strlen(delim) + 1))
// 			{
// 					delete_file(filename);
// 					close(fd);
// 					free(line);
// 					break;
// 			}
// 		}
// 	}
// }

// void here_doc(t_token **final)
// {
// 	int hc = 0;
// 	t_token *curr = *final;
// 	t_token *herecount = curr;
// 	while (herecount)
// 	{
// 		if (herecount->value == HEREDOC)
// 			hc++;
// 		if(hc == 17)
// 			return(printf("minishell : maximum here-document count exceeded\n"), exit(2));
// 		herecount = herecount->next;
// 	}
// 	while (curr)
// 	{
// 		if(curr->value == HEREDOC)
// 			here_doc_child(&curr);
// 		curr = curr->next;
// 	}
// }


char *randgen(char *s)
{
    char *pathname = "/dev/shm/";
    char *suffix = "\v";

    s = ft_strjoin(pathname, suffix);
    
    return s;
}

int file_to_write_on(char *filename)
{
    char *path = randgen(filename);
    int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
    free(path);
    return fd;
}

void delete_file(char *filename)
{
    unlink(filename);
}

void here_doc_child(t_token **final , int *fd1)
{
    t_token *curr = *final;
    int fd;
    char *line;
    char *filename = NULL;

    if (curr && curr->value == HEREDOC)
    {
        fd = file_to_write_on(filename);
        if (fd == -1)
        {
			delete_file(filename);
			fd = file_to_write_on(filename);
        }
        curr = free_spaces(curr->next);
        char *delim = curr->data;
        while (1)
        {
			delete_file(filename);
            line = readline(">");
            if (!line)
            {
                ft_printf(2, "warning: here-doc delimited by end-of-file\n");
                break;
            }
            if (!ft_strncmp(delim, line, ft_strlen(delim) + 1))
            {
				delete_file(filename);
				close(fd);
                free(line);
                break;
            }
            if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
                ft_printf(2, "Error: Unable to write to heredoc file\n");
            free(line);
        }
        close(fd);
        fd = open(filename, O_RDONLY);
        // if (fd != -1)
        // {
        //     dup2(fd, STDIN_FILENO);
        //     close(fd);
		// }
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
    while (herecount)
    {
        if (herecount->value == HEREDOC)
            hc++;
        if (hc == 17)
        {
            ft_printf(2, "minishell: maximum here-document count exceeded\n");
            exit(2);
        }
        herecount = herecount->next;
    }
    while (curr)
    {
        if (curr->value == HEREDOC)
            here_doc_child(&curr , &fd);
        curr = curr->next;
    }
	return (fd);
}
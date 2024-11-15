#include "../../includes/minishell.h"

// int **create_pipes(int *num_pipes) 
// {
//     int i;
//     int **pipes = malloc((*num_pipes) * sizeof(int *));
//     if (!pipes)
//         exit(1);
    
//     for (i = 0; i < *num_pipes; i++) 
// 	{
//         pipes[i] = malloc(2 * sizeof(int));
//         if (pipe(pipes[i]) == -1) {
//             perror("pipe");
//             exit(1);
//         }
//     }
//     return pipes;
// }

// void wait_children(int *num_pipes) 
// {
//     for (int i = 0; i < *num_pipes; i++) 
//         wait(NULL);
// }

// void heredoc_child(t_token **final, int *num_pipes, int **pipes) 
// {
//     t_token *curr = *final;
//     char *line = NULL;

//     // Close unused write ends in the child
//     for (int i = 0; i < *num_pipes; i++) 
// 	{
//         close(pipes[i][1]);
//     }

//     while (curr) 
// 	{
//         if (curr && curr->value == HEREDOC) 
// 		{
// 			curr = free_spaces(curr->next);
//             // curr = curr->next;
//             char *delim = curr->data;
// 			printf ("delim %s \n", delim);
//             while (1) 
// 			{
//                 line = get_next_line(0);
//                 if (!line)
//                     return; // Exit on EOF or error
//                 if (strncmp(line, delim, strlen(delim)) == 0) 
// 				{
//                     free(line);
//                     return;
//                 }
//                 free(line);
//             }
//         }
//         curr = curr->next;
//     }

//     // Close read ends after use
//     for (int i = 0; i < *num_pipes; i++) 
// 	{
//         close(pipes[i][0]);
//     }
// }

// void here_doc(t_token **final, int *num_pipes, int **pipes) 
// {
//     int id;
    
//     for (int i = 0; i < *num_pipes; i++) {
//         id = fork();
//         if (id == 0) 
// 		{
//             heredoc_child(final, num_pipes, pipes);
//             exit(0); // Ensure child exits
//         } 
// 		else if (id < 0) 
// 		{
//             perror("fork");
//             exit(1);
//         }

//         // Close both ends of the pipe in the parent after forking
//         close(pipes[i][1]); // Close write end
//     }
    
//     // Close all read ends in parent
//     for (int i = 0; i < *num_pipes; i++) 
// 	{
//         close(pipes[i][0]);
//     }
// }

// int here_doc_final(t_token **final) 
// {
//     int pc = 0;
//     int **pipes;

//     // Count HEREDOC tokens
//     t_token *curr = *final;
//     while (curr) 
// 	{
//         if (curr->value == HEREDOC)
//             pc++;
//         curr = curr->next;
//     }
    
//     pipes = create_pipes(&pc);
//     here_doc(final, &pc, pipes);
//     wait_children(&pc);

//     for (int i = 0; i < pc; i++) 
// 	{
//         free(pipes[i]);
//     }
//     free(pipes);
    
//     return 0;
// }
void print_inode(int fd) {
 struct stat info;
 if (fstat(fd, &info) != 0)
   fprintf(stderr,"fstat() error for fd %d: %s\n",fd,strerror(errno));
 else
   printf("The inode of fd %d is %d \n", fd, (int) info.st_ino);
}

void here_doc_child (t_token **final)
{
	t_token *curr = *final;
	int exit_status;

	int fd[2];
	int id = fork ();
	pipe(fd);

	if (id == 0)
	{
		dup2(fd[1] , 1);
		printf("fd[0] == %d\n" , STDIN_FILENO);
		if (curr && curr->value == HEREDOC)
		{
			curr = free_spaces(curr->next);
			print_inode(1);
			print_inode(fd[1]);
			char *delim = curr->data;
			while (1)
			{
				char *line = get_next_line(0);
				if(line)
				{
					write(fd[1] , line , strlen(line));
					if (!ft_strncmp(line , delim, ft_strlen(delim)))
					{
						close(fd[1]);
						free(line);
						exit(42);
					}
				}
			}
		}
	}
	close(fd[1]);
	waitpid (id, &exit_status, 0);
}

void here_doc(t_token **final)
{

	int hc = 0;
	t_token *curr = *final;
	t_token *herecount = curr;
	while (herecount)
	{
		if (herecount->value == HEREDOC)
			hc++;
		else if(hc == 17)
			return (printf("minishell : maximum here-document count exceeded\n"), exit(1));
		herecount = herecount->next;
	}
	while (curr)
	{
		if(curr->value == HEREDOC)
			here_doc_child(&curr);
		curr  = curr->next;
	}

	
}

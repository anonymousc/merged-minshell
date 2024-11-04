NAME = minishell

CFLAGS = #-fsanitize=address -g3 # -Wall -Wextra -Werror 


SRCS =  my_cd.c my_export.c my_echo.c my_env.c my_pwd.c utils.c my_unset.c #merged_parsing.c 

OBJ = $(SRCS:.c=.o)
%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC)  $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
	
NAME = minishell

CC = cc

CFLAGS = #-Werror -Wall -Wextra
CFLAGS += -fsanitize=address -g3

SRC = src/main.c src/minishell.c builtins/ft_env.c src/parsing/check_syntax.c src/parsing/heredoc.c src/parsing/Lexer_Tokens.c src/parsing/signals.c src/parsing/ft_split_v2.c src/parsing/debug.c execution/execute.c execution/my_env.c execution/my_export.c execution/my_cd.c execution/my_pwd.c execution/utils.c execution/my_echo.c src/parsing/expansion.c

LIBFTSRC =  $(wildcard src/libft/*.c src/libft/ft_printf/*.c src/libft/get_next_line/*.c)

OBJ = $(SRC:%.c=%.o) 

LIBFTOBJ = $(LIBFTSRC:%.c=%.o)

ARFILE = src/libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFTOBJ) $(ARFILE)
	$(CC) $(CFLAGS) $(OBJ) $(ARFILE) -lreadline -o $(NAME)

$(ARFILE) : $(LIBFTOBJ) 
	ar -rcs $(ARFILE) $(LIBFTOBJ)

clean :
	@rm -rf $(OBJ) $(LIBFTOBJ)
	@echo "\033[0;31mremoving obj files\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(ARFILE)
	@echo "\033[0;31mremoving archives and executables\033[0m"

re : fclean all

.PHONY : re all clean fclean

.SECONDARY : $(OBJ) $(LIBFTOBJ) $(ARFILE)

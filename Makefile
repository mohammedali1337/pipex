CC      = cc
CFLAGS  = -Wall -Wextra -Werror
SRC     = pipex_util/child.c pipex_util/ft_split.c pipex_util/lib_fonc.c pipex_util/str_trim.c pipex.c
OBJ     = $(SRC:.c=.o)
NAME    = pipex

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

pipex_util/%.o: pipex_util/%.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

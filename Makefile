NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra 

RM = rm -rf

C_FILES = builtins.c\
					ft_split.c\
					libft_needeed.c\
					handle_funcs_builtins.c\
					main.c\

OBJ = ${C_FILES:.c=.o}

all: ${NAME}

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -lreadline $^ -o $@

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME} ${OBJ}

re: fclean all

.PHONY : all re clean fclean
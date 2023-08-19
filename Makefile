NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra 

RM = rm -rf

C_FILES = builtins/echo.c\
					builtins/cd.c\
					builtins/env.c\
					builtins/pwd.c\
					builtins/exit.c\
					ft_split.c\
					libft_needeed.c\
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
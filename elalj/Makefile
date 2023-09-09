NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra

#CFLAGS = -Wall -Werror -Wextra  -fsanitize=address -g

RM = rm -rf

C_FILES = builtins/echo.c\
					builtins/cd.c\
					builtins/pwd.c\
					builtins/export.c\
					builtins/unset.c\
					builtins/env.c\
					builtins/exit.c\
					libft/ft_split.c\
					libft/libft.c\
					libft/libft_2.c\
					libft/libft_3.c\
					builtin_work.c\
					execute_cmd.c\
					execute_cmd_helper.c\
					pipe_work.c\
					main.c\
					#pipe_work_helper.c\

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
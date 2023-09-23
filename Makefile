# Define color variables using `tput`
# RED := $(shell tput setaf 1)
# RESET := $(shell tput sgr0)

GREEN = \033[1;95m
END =  \033[0m
PURPLE = \033[1;35m
BOLD = \033[1;95m

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra

# CFLAGS = -Wall -Werror -Wextra  -fsanitize=address -g

RM = rm -rf

C_FILES = elalj/builtins/echo.c\
		  elalj/builtins/cd.c\
		  elalj/builtins/pwd.c\
		  elalj/builtins/export.c\
		  elalj/builtins/unset.c\
		  elalj/builtins/env.c\
		  elalj/builtins/exit.c\
		  elalj/builtins/builtin_work.c\
		  elalj/libft/ft_split.c\
		  elalj/libft/libft.c\
		  elalj/libft/libft_2.c\
		  elalj/libft/libft_3.c\
		  elalj/execute_one_cmd/execute_cmd.c\
		  elalj/execute_one_cmd/execute_cmd_helper.c\
		  elalj/signal_handler.c\
		  0_main.c\
		  houmam/2_libft.c\
		  houmam/3_sp_characters.c\
		  houmam/4_split_cmd.c\
		  houmam/5_get_cmds.c\
		  houmam/6_expand_p1.c\
		  houmam/6_expand_p0.c\
		  houmam/6_expand_p00.c\
		  houmam/6_expand_p000.c\
		  houmam/8_heredoc.c\
		  houmam/9_redirections.c\
					
					
OBJ = ${C_FILES:.c=.o}

all: ${NAME}

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@ -lreadline
	@echo "$(PURPLE) $$MINI_SHELL $(END)"

%.o: %.c
	@echo "$(PURPLE)                                  Linking ... ⏳ $(END)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME} ${OBJ}

re: fclean all

.PHONY: all re clean fclean

# Define custom text with red color
define MINI_SHELL

    ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗     
    ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║     
    ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║     
    ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║     
    ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗
    ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝

	*********************  $(NAME) not ready ❌  *********************

endef
export MINI_SHELL
# $(NAME) is ready ✅
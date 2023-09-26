NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -I $(RL)/include

# CFLAGS = -Wall -Werror -Wextra  -fsanitize=address -g

RM = rm -rf

RL = ${shell brew --prefix readline}

RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m

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
		  elalj/pipes/pipes_handler.c\
		  elalj/pipes/setup_pipes.c\
		  elalj/perror.c\
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

%.o: %.c
	@echo "$(YELLOW)                                  Linking ...⏳$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ)
	@echo "$(GREEN)COMPILING... ⏳$(RESET)"
	@$(CC) -L $(RL)/lib $(CFLAGS) $^ -o $@ -lreadline
	@echo "$$MINI_SHELL"
	@echo "$(GREEN)COMPILATION COMPLETED ✅$(RESET)"

clean:
	@echo "$(RED)Deliting Obj_files ❌$(RESET)"
	@${RM} ${OBJ}

fclean: clean
	@echo "$(RED)Deliting Obj_files + Program ❌$(RESET)"
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

	*********************  $(NAME) in progress ⏳  *********************

endef
export MINI_SHELL
# $(NAME) is ready ✅
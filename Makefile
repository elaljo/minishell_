NAME = minishell

CC = cc

CFLAGS =  -I $(RL)/include -g



RM = rm -rf

RL = ${shell brew --prefix readline}

RESET = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
END =  \033[1;0m
PURPLE = \033[1;35m

C_FILES = elalj/builtins/echo.c\
		  elalj/builtins/cd.c\
		  elalj/builtins/pwd.c\
		  elalj/builtins/export.c\
			elalj/builtins/export_helper.c\
		  elalj/builtins/unset.c\
		  elalj/builtins/env.c\
		  elalj/builtins/exit.c\
		  elalj/builtins/builtin_work.c\
		  elalj/libft/ft_split.c\
		  elalj/libft/libft.c\
		  elalj/libft/libft_2.c\
		  elalj/libft/libft_3.c\
			elalj/libft/libft_4.c\
		  elalj/execute_one_cmd/execute_cmd.c\
		  elalj/execute_one_cmd/execute_cmd_helper.c\
		  elalj/signal_handler.c\
		  elalj/pipes/pipes_handler.c\
		  elalj/pipes/setup_pipes.c\
		  elalj/redir/execute_redir.c\
			elalj/redir/redir_helper.c\
		  elalj/perror.c\
			elalj/main_helper.c\
		  0_main.c\
		  houmam/0_others.c\
		  houmam/1_errors_p2.c\
		  houmam/1_errors.c\
		  houmam/2_libft_p2.c\
		  houmam/2_libft.c\
		  houmam/3_sp_characters.c\
		  houmam/4_split_cmd_p2.c\
		  houmam/4_split_cmd.c\
		  houmam/5_get_cmds_p2.c\
		  houmam/5_get_cmds.c\
		  houmam/6_dollar_split_p2.c\
		  houmam/6_dollar_split.c\
		  houmam/6_expand_p2.c\
		  houmam/6_expand_redir.c\
		  houmam/6_expand.c\
		  houmam/6_quote_split_p2.c\
		  houmam/6_quote_split.c\
		  houmam/6_quotes_check.c\
		  houmam/9_redirections.c\

OBJ = ${C_FILES:.c=.o}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ)
	@echo "$(GREEN)                                    COMPILING... ⏳$(RESET)"
	@echo "$(YELLOW)                                     Linking... ⏳$(RESET)"
	@$(CC) -L $(RL)/lib $(CFLAGS) $^ -o $@ -lreadline
	@echo "$(GREEN)                                COMPILATION COMPLETED💲 ✔️$(RESET)"
	@echo "$(PURPLE) $$MINI_SHELL $(END)"

clean:
	@echo "$(RED)                                 Removing Obj_files ✔️$(RESET)"
	@${RM} ${OBJ}

fclean: clean
	@echo "$(RED)                              Removing Obj && minishell ✔️$(RESET)"
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

	*********************  $(NAME) is ready ✅  *********************

endef
export MINI_SHELL
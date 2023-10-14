/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:16:38 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 20:09:46 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/wait.h>
# include <fcntl.h>

int	g_exit_status;

typedef struct s_exp
{
	char	**argu;
	int		i;
	int		j;
	int		k;
	int		quoted;
	int		empty;
	char	*tmp;
	char	*joigned_0;
	char	*joigned_1;
	char	**quote_splitted;
	char	**dollar_splitted;
}	t_exp;

typedef struct s_sp
{
	int	i;
	int	j;
	int	k;
	int	start;
	int	wrds;
	int	sq;
	int	dq;
	int	end;
	int	len;
}	t_sp;

typedef struct s_init
{
	char	*input_string;
	char	**splitted_cmds;
	char	**splitted;
}	t_init;

typedef struct s_redi
{
	char	*redi;
	char	*eof;
}	t_redi;

typedef struct s_cmd
{
	int		argu_nbr;
	char	**argu;
	char	**args;
	int		redir_nbr;
	int		cmd_len;
	char	*path;
	t_redi	*redir;
	t_redi	*redii;
}	t_cmd;

typedef struct s_quote
{
	int	sq;
	int	dq;
	int	cnt;
}	t_quote;

typedef struct s_ndx
{
	int	i;
	int	j;
	int	k;
	int	len;
	int	nbr;
	int	red;
	int	check;
	int	check_space;
	int	pipe;
	int	start;
	int	cnt;
	int	brk;
}	t_ndx;

typedef struct s_data
{
	char	**c_env;
	int		len_env;
	char	**key_env;
	int		new_st;
	int		old_st;
	int		pid;
	int		pipe_fd[2];
	char	*tmp;
	char	*line;
	int		quoted;
}t_data;

/* - - - - - - - - - - - - - - Splitter - - - - - - - - - - - - - - */
int			count(char *str);
int			handle_redir(char *str, char **tab, t_ndx *ndx, t_quote quote);
int			handle_pipe(char **tab, t_ndx *ndx, char *str);
char		**split(char *str);
int			count_cmds(char **tab);
void		removing_spaces(char **str);

/* - - - - - - - - - - - - - - libft - - - - - - - - - - - - - - */
int			ft_tablen(char **tab);
char		**split_str(char *str, char c);
int			cnt_wrds(char *str, char c);
int			only_spaces(char *str);
int			nbr_l(int n);
char		*ft_itoa(int n);
// houmam
char		*handle_quoted(char *str);
int			check_quoted(char *str);
int			count_cmds(char **tab);
int			cmd_len(char **tab);
t_cmd		*get_cmds(char **tab, t_data *data);
void		get_cmds_p0(char **tab, int *comnd_len, t_cmd *cmds, t_ndx *n);
void		get_cmds_p1(char **tab, int *comnd_len, t_cmd *cmds, t_ndx *n);
int			get_cmds_p2(char **tab, t_cmd *cmds, t_ndx *n);
int			get_cmds_p3(char **tab, t_cmd *cmds, t_ndx *n);
void		get_cmds_p4(char **tab, int *comnd_len, t_cmd *cmds, t_ndx *n);
void		get_cmds_p5(t_data *data, t_cmd *cmds, t_ndx *n);
int			cnt_redir(char **tab);
int			cnt_exp(char *str);
char		**quotes_split(char *str);
int			cnt_dollars(char *str);
int			is_var(char c);
char		**dollar_split(char *str);
char		*expand_var(char *str, t_data data);
void		expander(t_cmd *cmd, int len, t_data *data);
void		expand_herdoc(char **str, t_data *data);
void		expand_all(t_cmd *cmds, t_data *data);
int			check_in_env(t_data data, char *var);
t_quote		unclosed_quotes(char *str);
int			parsing_errors(char *str);
void		ft_trim(char **str, int i);
int			successive_redir(char *str);
int			redir_errors(t_cmd *cmds);
void		cp_redir(t_cmd *cmds, int j, t_data *data);
void		expand_redir(t_cmd *cmds, int i, int j, t_data *data);
char		**rm_empty(char **tab);
void		rm_empty_p2(char **tab, char **tmp, int *i, int *cnt);
char		**tab_dup(char **tab);
int			cmd_pipe(char **tab, t_cmd *cmds);
void		free_cmds(t_cmd *cmds);
int			is_redir(char *str);
////////////// Added recently
void		put_error(char *str);
// mohamed
void		executer(t_cmd *cmds, t_data *data);
void		ctrl_d(t_data *data, char *input_string);
void		set_exit_status(t_data *data);
void		init_data_structs(t_data *data);
void		copy_env(t_data *data, char **env);
void		execute_builtin(t_cmd *cmd, t_data *data, int i);
int			is_builtin(char *cmd);
int			valid_num(char *str);
void		if_there_var(t_cmd *cmd, t_data *data, int I);
void		print_not_identifier_ex(char *line, t_data *data);
void		print_not_identifier_un(char *line, t_data *data);
void		get_key(t_data *data, int n_arg);
int			same_key(t_data *data, char *line);
void		remove_key(t_data *data, char *line);
void		print_if_exit_valid(char *line, t_data *data);
char		**ft_realloc(char **s, size_t size);
//	execute_cmd
void		executing_one_cmd(t_cmd *cmd, int i, t_data *data);
void		found_cmd(t_cmd *cmd, int op, t_data *data);
char		*get_cmd_path(t_data *data, char *cmd);
void		execute_cmd(t_cmd *cmd, int i, t_data *data);
void		open_dir_err(t_cmd *cmd, int op);
void		printf_no_file_no_dir(char *cmd);
char		*get_full_path(t_data *data, char *str);
//	builtins
void		my_echo(t_cmd *cmd, int i, int a);
void		handle_my_echo(t_cmd *cmd, int i);
int			check_first_n(t_cmd *cmd, int i);
int			check_n_n(t_cmd *cmd, int i, int a);
void		option_n(t_cmd *cmd, int i);
void		my_cd(t_cmd	*cmd, int i, t_data *data);
void		export_old_pwd(char *old_pwd, t_data *data);
void		export_pwd(t_data *data);
char		*get_old_pwd(void);
int			run_cd_only(t_data *data, char *home_dir);
void		my_pwd(void);
void		my_export(t_cmd *cmd, t_data *data, int I);
void		print_export(t_data *data, int i, int check);
int			export_arg_count(t_cmd *cmd, int I);
int			export_total_arg(t_cmd *cmd, int I);
void		my_unset(t_cmd *cmd, t_data *data, int i);
int			count_arg_un(t_cmd *cmd, int i);
void		my_env(t_data *data);
void		my_exit(t_cmd *cmd, int i, t_data *data);
char		*my_getenv(char *name, t_data *data);
//	pipes
void		execute_pipe(t_cmd *cmd, t_data *data);
void		start_executing_pipe(t_cmd *cmd, t_data *data,
				int fd1[2], int fd2[2]);
void		setup_pipes(int fd1[2], int fd2[2], int i, t_cmd *cmd);
void		gives_pipe_to_the_next_child(int fd1[2], int fd2[2], int i);
void		first_cmd(int fd1[2], int fd2[2]);
void		pair(int fd1[2], int fd2[2]);
void		unpair(int fd1[2], int fd2[2]);
void		last_unpair(int fd1[2], int fd2[2]);
void		last_pair(int fd1[2], int fd2[2]);
void		close_pipes(int fd1[2], int fd2[2]);
//	redir
void		redir_output(char *eof);
void		redir_append(char *eof);
void		redir_input(char *eof);
int			execute_heredoc(char *eof, t_data *data);
void		execute_redir(t_cmd *cmd, t_data *data);
void		setup_redir(t_cmd *cmd, t_data *data, int i);
void		exit_status_func(t_data *data);
//	signals
void		signal_handler(int signum);
void		signal_part(void);
void		signal_herdoc(int signum);
//			split
int			is_delimiter(char c);
int			words_len(char *s);
char		*get_word(char *str);
char		**ft_split(char *str);
//	libft
char		*ft_strdup(char *str);
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *s);
void		ft_putstr_fd(char *s, int fd);
int			ft_search(char *line, char space);
int			ft_isalpha(char c);
int			ft_isalnum(char *c);
char		*ft_strchr(const char *s, char c);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
//my_libft_helper
char		*strback(char *line);
void		ft_str_free(char **arr);
int			len_arr(char **arr);
//	perror
void		perror_pipe(void);
void		perror_fork(void);
void		perror_fd(void);
void		perror_execve(void);

#endif
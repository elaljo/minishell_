/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:16:38 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/17 17:39:28 by hait-sal         ###   ########.fr       */
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

typedef struct s_redi
{
	char	*redi;//redirection and type will be defined later
	char	*eof;//eof
} t_redi;

typedef struct s_cmd
{
	int		args_nbr;//che7al mn commande machi arg
	char	**args;//command + args
	t_redi	*redir;//redirections type + eof
	int		redir_nbr;//redirection number
	int		cmd_len;
	char	*path;
} t_cmd;

typedef	struct s_quote
{
	int sq;
	int dq;
} t_quote;

typedef	struct s_ndx
{
	int i;
	int j;
	int k;
	int check;
	int check_space;
	int pipe;
	int start;
	int cnt;
} t_ndx;

typedef struct s_data
{
	char	**c_env;
	int		len_env;
	char	**key_env;
}t_data;

/* - - - - - - - - - - - - - - Splitter - - - - - - - - - - - - - - */
int		count(char *str);
int		handle_redir(char *str, char **tab, t_ndx *ndx, t_quote quote);
int		handle_pipe(char **tab, t_ndx *ndx, char *str);
char	**split(char *str);
int		count_cmds(char **tab);
char	*rm_spaces(char *str);
void	removing_spaces(char **str);

/* - - - - - - - - - - - - - - libft - - - - - - - - - - - - - - */

/**
 * duplicate a string using malloc
 * @param str the string to be duplicated
 * @return the duplicated string.
 */
int		ft_tablen(char **tab);
char    **split_str(char *str, char c);
int		cnt_wrds(char *str, char c);
int		only_spaces(char *str);
// char	*tab_join(char **tab);

// houmam

char	*expand_variables(char* input);
void	expand_variable(const char* var_name, char* expanded, size_t* j);
int		is_alnum(char c);
t_cmd	*expandables(t_cmd *cmds);
char	*handle_quoted(char *str);
int		check_quoted(char *str);
int		count_cmds(char **tab);
int		cmd_len(char **tab);
t_cmd	*get_cmds(char **tab);
int		cnt_redir(char **tab);
int		cnt_exp(char *str);
char    **quotes_split(char *str);
int		cnt_dollars(char *str);
int		is_var(char c);
char    **dollar_split(char *str);
char    *expand_var(char *str, t_data data);
void    expander(t_cmd *cmd, int len, t_data data);
void    expand_all(t_cmd *cmds, t_data data);
int		check_in_env(t_data data, char *var);

// moahmed

void	init_data_structs(t_data *data);
void	copy_env(t_data *data, char **env);
void	execute_builtin(t_cmd *cmd, t_data *data, int i);
int		is_builtin(char *cmd);
int		valid_num(char *str);
void	if_there_var(t_cmd *cmd, t_data *data, int I);
void	print_not_identifier_ex(char *line);
void	print_not_identifier_un(char *line);
void	get_key(t_data *data, int n_arg);
int		same_key(t_data *data, char *line);
void	remove_key(t_data *data, char *line);
void	print_if_exit_valid(char *line);

//	execute_cmd
void	executing_one_cmd(t_cmd *cmd, int i, t_data *data);
void	found_cmd(t_cmd *cmd, int op, t_data *data);
char	*get_cmd_path(t_data *data, char *cmd);
void	execute_cmd(t_cmd *cmd, int i, t_data *data);
void	open_dir_err(t_cmd *cmd, int op);

//	builtins
void	my_echo(t_cmd *cmd, int i, int a);
void	handle_my_echo(t_cmd *cmd, int i);
void	my_cd(t_cmd	*cmd, int i, t_data *data);
void	export_old_pwd(char *old_pwd, t_data *data);
void	export_pwd(t_data *data);
void	my_pwd(void);
void	my_export(t_cmd *cmd, t_data *data, int I);
void	print_export(t_data *data ,int i, int j, int check);
void	my_unset(t_cmd *cmd, t_data *data, int i);
void	my_env(t_data *data);
void	my_exit(t_cmd *cmd, int i);

//	pipes
void    execute_pipe(t_cmd *cmd, t_data *data);
void    start_executing_pipe(t_cmd *cmd, t_data *data, int fd1[2], int fd2[2]);
void    setup_pipes(int fd1[2], int fd2[2], int i, t_cmd *cmd);
void    gives_pipe_to_the_next_child(int fd1[2], int fd2[2], int i);
void	first_cmd(int fd1[2], int fd2[2]);
void	pair(int fd1[2], int fd2[2]);
void	unpair(int fd1[2], int fd2[2]);
void	last_unpair(int fd1[2], int fd2[2]);
void	last_pair(int fd1[2], int fd2[2]);
void    close_pipes(int fd1[2], int fd2[2]);

//	signals
void    signal_handler(int signum);
void    signal_part();

//			split
int		is_delimiter(char c);
int		words_len(char *s);
char	*get_word(char *str);
char	**ft_split(char *str);

//	libft
char	*ft_strdup(char *str);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_search(char *line, char space);
int		ft_isalpha(char c);
int		ft_isalnum(char *c);
char	*ft_strchr(const char *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
//my_libft_helper
char	*strback(char *line);
void	ft_str_free(char **arr);
int		len_arr(char **arr);

//	perror
void    perror_pipe(void);
void    perror_fork(void);

char	*ft_strtrim(char  *s1, char  *set);

#endif
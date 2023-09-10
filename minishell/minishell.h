/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:21:34 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/27 20:21:35 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
#	include <string.h>
# include <unistd.h> //fork() getcwd() chdir()
# include <stdlib.h> //get_env()
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h> //wait()
# include	<dirent.h> //opendir()

// homam--------------------------- 1111111111111----------------------------------
typedef struct s_cmd
{
	int		nbr;
	char	*cmd;
	char	**args;
	char	*path;
	char **split_cmd;
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
	int start;
	int cnt;
} t_ndx;

/* - - - - - - - - - - - - - - Splitter - - - - - - - - - - - - - - */
int		count(char *str);
int		handle_redir(char *str, char **tab, t_ndx *ndx, t_quote quote);
int		handle_pipe(char **tab, t_ndx *ndx);
char	**split(char *str);
int count_cmds(char **tab);

/* - - - - - - - - - - - - - - libft - - - - - - - - - - - - - - */

/**
 * duplicate a string using malloc
 * @param str the string to be duplicated
 * @return the duplicated string.
 */
char	*ft_strdup(char *str);
int		ft_tablen(char **tab);
char    **split_str(char *str, char c);
int		cnt_wrds(char *str, char c);
int	only_spaces(char *str);
// char	*tab_join(char **tab);



char	*expand_variables(char* input);
void	expand_variable(const char* var_name, char* expanded, size_t* j);
int		is_alnum(char c);
t_cmd	*expandables(t_cmd *cmds);
void	handle_quoted(char *str);
int check_quoted(char *str);
int count_cmds(char **tab);
int cmd_len(char **tab);
t_cmd	*get_cmds(char **tab);

// elalj -----------------22222222---------------------------
typedef struct s_data
{
	char	**c_env;
	int		len_env;
	char	**key_env;
}t_data;

//typedef struct s_cmd
//{
//	char	*cmd;
//	char	**cmd_args;
//	char	*path;
//	char	**split_cmd;
//	int		op_pipe;
//}t_cmd;

void	init_data_structs(t_data *data);
void	copy_env(t_data *data, char **env);
void	execute_builtin(t_cmd *cmd, t_data *data);
int		is_builtin(t_cmd *cmd);
int		valid_num(char *str);
void	if_there_var(t_cmd *cmd, t_data *data);
void	print_not_identifier_ex(char *line);
void	print_not_identifier_un(char *line);
void	get_key(t_data *data, int n_arg);
int		same_key(t_data *data, char *line);
void	remove_key(t_data *data, char *line);
void	print_if_exit_valid(char **line);

//execute_cmd
void	found_cmd(char **line, t_cmd *cmd, char **env, int op);
void	get_path(char **env, t_cmd *cmd);
void	split_path (char **line, t_cmd *cmd, int op);
char	*check_if_valid_cmd(t_cmd *cmd);
void	execute_cmd(char **line, t_cmd *cmd, int op);
void	open_dir_err(char **line, int op);
void	already_valid_path_exec(char **line, int op);

//	builtins
void	my_echo(t_cmd *cmd, int i);
void	handle_my_echo(t_cmd *cmd);
void	my_cd(t_cmd	*cmd);
void	my_pwd(void);
void	my_export(t_cmd *cmd, t_data *data);
void	my_unset(t_cmd *cmd, t_data *data);
void	my_env(t_data *data);
void	my_exit(char **line);

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



#endif

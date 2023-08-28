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
# include <unistd.h> //fork() getcwd() chdir()
# include <stdlib.h> //get_env()
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	**c_env;
	int		len_env;
	char	**key_env;
}t_data;

void	init_data(t_data *data);

void	copy_env(t_data *data, char **env);
void	execute_builtin(char **line, t_data *data);
int		is_builtin(char **line);
int		valid_num(char *str);
void	if_there_var(char **line, t_data *data);
void	print_not_identifier_ex(char *line);
void	print_not_identifier_un(char *line);
void	get_key(t_data *data, int n_arg);
int		same_key(t_data *data, char *line);
void	remove_key(t_data *data, char *line);
void	print_if_exit_valid(char **line);

//	builtins
void	my_echo(char **args, int i);
void	handle_my_echo(char **line);
void	my_cd(char **line);
void	my_pwd(void);
void	my_export(char **line, t_data *data);
void	my_unset(char **line, t_data *data);
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

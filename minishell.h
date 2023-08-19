#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h> //fork() getcwd() chdir()
#include <stdlib.h> //get_env()
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_data
{
	char **c_env;

}t_data;

void	init_data(t_data *data);

void	copy_env(t_data *data, char **env);
void	execute_builtin(char **line, t_data *data);
int		is_builtin(char **line);
int	valid_num(char *str);

//handle_builtins
void	handle_my_echo(char **line);
void	my_cd(char **line);
void	my_exit(char **line);

//	builtins
void	my_echo(char **args, int i);
void	my_pwd(void);
void	my_env(t_data *data);

//			split
int is_delimiter(char c);
int words_len(char *s);
char	*get_word(char *str);
char	**ft_split(char *str);

//	libft
char	*ft_strdup(char *str);
int	ft_atoi(const char *str);
int	ft_strcmp(const char *s1, const char *s2);
size_t ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);

#endif
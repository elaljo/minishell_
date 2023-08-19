/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:16:02 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/18 19:37:14 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(char **line, t_data *data)
{
	if (ft_strcmp(line[0], "echo") == 0)
		handle_my_echo(line);
	else if(ft_strcmp(line[0], "cd") == 0)
		my_cd(line);
	else if (ft_strcmp(line[0], "pwd") == 0)
		my_pwd();
	else if (ft_strcmp(line[0], "exit") == 0)
		handle_exit(line);
	else if (ft_strcmp(line[0], "env") == 0)
		my_env(data);
}

int	is_builtin(char **line)
{
	char *arr[] = {"echo", "cd", "pwd", "exit", "env", "export", NULL};
	int i;

	i = -1;
	while (arr[++i])
	{
		if (ft_strcmp(line[0], arr[i]) == 0)
			return (1);
	}
	return (0);
}

void	my_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->c_env[i] != NULL)
	{
		printf("%s\n", data->c_env[i]);
		i++;
	}
}

void	my_pwd(void)
{
	char c_dir[256];

	if (getcwd(c_dir, sizeof(c_dir)) != NULL)
		printf("%s\n", c_dir);
	else
		perror("getcwd err");
}

void	my_echo(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != 0)
			printf(" ");
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_work.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:04:54 by moelalj           #+#    #+#             */
/*   Updated: 2023/09/04 18:04:54 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	execute_builtin(char **line, t_data *data)
{
	if (ft_strcmp(line[0], "echo") == 0)
		handle_my_echo(line);
	else if (ft_strcmp(line[0], "cd") == 0)
		my_cd(line);
	else if (ft_strcmp(line[0], "pwd") == 0)
		my_pwd();
	else if (ft_strcmp(line[0], "export") == 0)
		my_export(line, data);
	else if (ft_strcmp(line[0], "unset") == 0)
		my_unset(line, data);
	else if (ft_strcmp(line[0], "env") == 0)
		my_env(data);
	else if (ft_strcmp(line[0], "exit") == 0)
		my_exit(line);
}

int	is_builtin(char **line)
{
	char	*arr[] = {"echo", "cd", "pwd", "exit", "env", "export", "unset", NULL};
	int		i;

	i = -1;
	while (arr[++i])
	{
		if (ft_strcmp(line[0], arr[i]) == 0)
			return (1);
	}
	return (0);
}

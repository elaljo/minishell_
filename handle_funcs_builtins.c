/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_funcs_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:37:27 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/18 19:37:28 by moelalj          ###   ########.fr       */
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

void	my_cd(char **line)
{
	char *home_dir;

	home_dir = getenv("HOME");
	if (ft_strcmp(line[0], "cd") == 0 && (!line[1] || ft_strcmp(line[1], "~") == 0))
	{
		if (chdir((const char *)home_dir) == 0)
			chdir((const char *)home_dir);
	}
	else if (line[1] && ft_strcmp(line[0], "cd") == 0)
	{
		if(chdir(line[1]) == 0)
			chdir(line[1]);
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(line[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}
}

void	handle_exit(char **line)
{
	if (line[1])
	{
		if (valid_num(line[1]) == 0)
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(line[1], 2); 
			ft_putstr_fd(": numeric argument required\n", 2);
			exit (255);
		}
		else if (line[2] && line[1])
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return ;
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			exit(ft_atoi(line[1]));
		}
	}
}

void	handle_my_echo(char **line)
{
	int	i;

	i = 1;
	if(line[i] && line[i][0] == '-' && line[i][1] == 'n')
		my_echo(line, i + 1);
	else if (line[i])
	{
		my_echo(line, i);
		printf("\n");
	}
	else
		printf("\n");
}


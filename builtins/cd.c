/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:48:37 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/19 20:48:37 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

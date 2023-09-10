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

#include "../../minishell.h"

void	my_cd(t_cmd *cmd)
{
	char	*home_dir;
	int		check;

	check = 0;
	home_dir = getenv("HOME");
	if (!cmd[0].args[0])
		check = chdir((const char *)home_dir);
	else
		check = chdir(cmd[0].args[0]);
	if (check != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd[0].cmd, 2);
		ft_putstr_fd(": ", 2);
		perror(cmd[0].args[1]);
	}
}

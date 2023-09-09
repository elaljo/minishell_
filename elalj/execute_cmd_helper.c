/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 00:03:47 by moelalj           #+#    #+#             */
/*   Updated: 2023/09/05 00:03:48 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_dir_err(char **line, int op)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(line[op], 2);
	ft_putstr_fd(": is a directory\n", 2);
}

void	already_valid_path_exec(char **line, int op)
{
	int	pid_f;

	pid_f = fork();
	if (pid_f == -1)
		perror("fork");
	else if (pid_f == 0)
	{
		if (execve(line[op], line, NULL) == -1)
			perror("execve");
	}
	else
		wait(NULL);
}

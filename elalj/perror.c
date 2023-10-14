/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:54:18 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/14 13:20:23 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	perror_pipe(void)
{
	perror("pipe");
	exit (1);
}

void	perror_fork(void)
{
	perror("fork");
	exit (1);
}

void	perror_fd(void)
{
	perror("fd");
	exit (1);
}

void	perror_execve(void)
{
	perror("execve");
	exit (1);
}

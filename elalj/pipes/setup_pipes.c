/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:36:29 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/14 13:36:32 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	first_cmd(int fd1[2], int fd2[2])
{
	dup2(fd1[1], 1);
	close(fd2[0]);
	close(fd2[1]);
	close(fd1[1]);
	close(fd1[0]);
}

void	unpair(int fd1[2], int fd2[2])
{
	dup2(fd1[0], 0);
	dup2(fd2[1], 1);
	close(fd2[1]);
	close(fd2[0]);
	close(fd1[1]);
	close(fd1[0]);
}

void	pair(int fd1[2], int fd2[2])
{
	dup2(fd2[0], 0);
	dup2(fd1[1], 1);
	close(fd2[0]);
	close(fd1[1]);
	close(fd1[0]);
	close(fd2[1]);
}

void	last_pair(int fd1[2], int fd2[2])
{
	dup2(fd2[0], 0);
	close(fd2[0]);
	close(fd2[1]);
	close(fd1[0]);
	close(fd1[1]);
}

void	last_unpair(int fd1[2], int fd2[2])
{
	dup2(fd1[0], 0);
	close(fd1[1]);
	close(fd1[0]);
	close(fd2[0]);
	close(fd2[1]);
}

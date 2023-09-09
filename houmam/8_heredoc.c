/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:52:44 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/09 21:09:24 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	ft_putstr_fd(int fd, char *str)
{
	int i = 0;

	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}
void	heredoc(char *eof)
{
	int fd[2];
	char *input;
	char *heredoc;

	pipe(fd);
	// int fd = open("heredoc.txt", O_RDWR | O_CREAT);
	char *tmp1;
	char *tmp2;
	while (1)
	{
		input = readline("heredoc> ");
		if (ft_strcmp(eof, input) == 0)
			break ;
		ft_putstr_fd(fd[1], input);
	}
	dup2(fd[0], 0);
}

int main()
{
	heredoc("test");
}
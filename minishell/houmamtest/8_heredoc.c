/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:52:44 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/10 16:00:44 by hait-sal         ###   ########.fr       */
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
int	heredoc(char *eof)
{
	int fd[2];
	char *input;
	char *heredoc;

	pipe(fd);
	while (1)
	{
		input = readline("heredoc> ");
		if (ft_strcmp(eof, input) == 0)
			break ;
		ft_putstr_fd(fd[1], input);
	}
	close(fd[1]);
	return (fd[0]);
}

// int main()
// {
// 	int fd = heredoc("test");
// 	char str[100];
// 	int r = read(fd, str, 20);
// 	str[r] = 0;
// 	printf("str: %s\n", str);
// }
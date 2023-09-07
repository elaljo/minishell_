/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:31 by moelalj           #+#    #+#             */
/*   Updated: 2023/09/06 16:57:32 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_pipes(char **line)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (line[i])
	{
		if (ft_search(line[i], '|'))
			c++;
		i++;
	}
	return (c);
}

void	execute_pipe(char **line, t_cmd *cmd, char **env)
{
	(void)line;
	(void)cmd;
	int	fd1[2];
	//int fd2[2];
	int	pid_f;

	if (pipe(fd1) == -1)
		perror("pipe");
	pid_f = fork();
	if (pid_f == -1)
		perror("fork");
	else if (pid_f == 0)
	{
		close(fd1[0]);
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[1]);
		char *arr[10] = {"ls", "-l", NULL};
		execve("/bin/ls", arr, env);
		//found_cmd(line, cmd, env, 0);
	}
	int	pid2 = fork();
	if (pid2 == -1)
		perror("fork");
	else if (pid2 == 0)
	{
		close(fd1[1]);
		dup2(fd1[0], STDIN_FILENO);
		close(fd1[0]);
		//found_cmd(line, cmd, env, 2);
		char *arr[10] = {"wc", "-l", NULL};
		execve("/usr/bin/wc", arr, env);
	}
	else
	close(fd1[0]);
	close(fd1[1]);
	waitpid(pid_f, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	is_pipe(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_search(line[i], '|'))
			return (1);
		i++;
	}
	return (0);
}

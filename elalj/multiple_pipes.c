#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, strlen(s));
}

void	first_cmd(int fd1[2], int fd2[2])
{
	dup2(fd1[1], 1);
	close(fd2[0]);
	close(fd2[1]);
	close(fd1[1]);
	close(fd1[0]);
}
void	pair(int fd1[2], int fd2[2])
{
	dup2(fd1[0], 0);
	dup2(fd2[1], 1);
	close(fd2[1]);
	close(fd2[0]);
	close(fd1[1]);
	close(fd1[0]);
}
void	unpair(int fd1[2], int fd2[2])
{
	dup2(fd2[0], 0);
	dup2(fd1[1], 1);
	close(fd2[0]);
	close(fd1[1]);
	close(fd1[0]);
	close(fd2[1]);
}
void	last_unpair(int fd1[2], int fd2[2])
{
	dup2(fd2[0], 0);
	close(fd2[0]);
	close(fd2[1]);
	close(fd1[0]);
	close(fd1[1]);
}
void	last_pair(int fd1[2], int fd2[2])
{
	dup2(fd1[0], 0);
	close(fd1[1]);
	close(fd1[0]);
	close(fd2[0]);
	close(fd2[1]);
}

char **get_array(char *cmd)
{
	char	**arr;

	arr = malloc(2 * sizeof(char *));
	arr[0] = strdup(cmd);
	arr[1] = NULL;
	return (arr);
}

int arr_len(char **arr)
{
	int i;

	i = 1;
	while (arr[i])
		i++;
	i--;
	return (i);
}
void	setup_pipes(int fd1[2], int fd2[2], int i, int len)
{
	if (i == 1)
		first_cmd(fd1, fd2);
	else if ((i == len) && (i % 2 != 0))
		last_unpair(fd1, fd2);
	else if((i == len) && (i % 2 == 0))
		last_pair(fd1, fd2);
	else if (i % 2 != 0)
		unpair(fd1, fd2);
	else if (i % 2 == 0)
		pair(fd1, fd2);
}
int main(int ac, char *av[], char **env)
{
	int	fd1[2];
	int fd2[2];
	int pid;
	int	i;
	int len;

	if (pipe(fd1) == -1 || pipe(fd2) == -1)
	{
		perror("pipe");
		exit(1);
	}
	len = arr_len(av);
	i = 1;
	while (i <= len)
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			setup_pipes(fd1, fd2, i, len);
			if (execve(av[i], get_array(av[i]), NULL) == -1)
			{
				ft_putstr_fd(av[i], 2);
				ft_putstr_fd("\n", 2);
				perror("execve");
				exit(1);
			}
		}
		if (i % 2 == 0)
		{
			close(fd1[0]);
			close(fd1[1]);
			pipe(fd1);
		}
		else
		{
			close(fd2[0]);
			close(fd2[1]);
			pipe(fd2);
		}
		i++;
	}
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	i = 1;
	while (i <= len)
	{
	waitpid(pid, NULL, 0);
		i++;
	}
}

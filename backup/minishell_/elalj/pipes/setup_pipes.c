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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:58:13 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/14 13:21:36 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_part(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		perror("signal");
}

void	signal_herdoc(int signum)
{
	if (signum == SIGINT)
		exit(1);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
	if (signum == SIGQUIT)
		exit (131);
}

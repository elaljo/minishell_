#include "../minishell.h"

void    signal_part()
{
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		perror("signal");
}

void    signal_herdoc(int signum)
{
    if (signum == SIGINT)
    {
        //g_exit_status = 1;
        exit(1);
    }
}

void    signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
        // g_exit_status = 1;
    }
}

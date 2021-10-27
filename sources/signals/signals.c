#include <signals.h>

void	gsignal_ctlc(int sigtype)
{
	if (sigtype == SIGINT)
	{
		write(1, "\rminishell-2.0$   \n", 20);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	fsignal_ctlc(int sigtype)
{
	if (sigtype == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:30:35 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/05 16:06:12 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signals.h>
#include <utilities.h>

void	gsignal_ctlc(int sigtype)
{
	if (sigtype == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	fsignal_ctlc(int sigtype)
{
	if (sigtype == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	changetermios(bool toggle)
{
	struct termios	term;

	if (tcgetattr(STDOUT_FILENO, &term) == -1)
		return (1);
	if (toggle)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &term) == -1)
		return (1);
	return (0);
}

void	heredoc_ctlc(int sigtype)
{
	if (sigtype == SIGINT)
	{
		close(0);
		write(2, "\n", 1);
	}
}

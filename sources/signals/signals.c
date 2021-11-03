/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:30:35 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/03 21:32:24 by nschumac         ###   ########.fr       */
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

static int	ft_memappend(void **p1, size_t p1_size, void *p2, size_t p2_size)
{
	void	*newp1;

	newp1 = malloc(p1_size + p2_size + 1);
	if (!newp1)
		return (1);
	ft_memcpy(newp1, *p1, p1_size);
	ft_memcpy(newp1 + p1_size, p2, p2_size);
	if (*p1)
		free(*p1);
	*p1 = newp1;
	return (0);
}

int	our_minishell(char *cmd)
{
	int		fd;
	char	*str1;
	char	str2[1001];
	int		ret;
	int		total;

	fd = open(cmd, O_RDONLY);
	if (fd < 0)
		return (0);
	total = 0;
	ret = read(fd, str2, 1000);
	str1 = 0;
	while (ret)
	{	
		if (ft_memappend((void **)&str1, total, (void *)str2, ret))
			return (0);
		total += ret;
		ret = read(fd, str2, 1000);
	}
	if (total >= 30
		&& !ft_strncmp(str1 + total - 30, "42-minishell@nschumac,jsiller", 29))
	{
		free(str1);
		return (1);
	}
	if (str1)
		free(str1);
	return (0);
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

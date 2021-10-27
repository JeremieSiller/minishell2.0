/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:12 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/27 02:55:13 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <utilities.h>
#include <execute.h>

void signalg(int sigtype)
{
	if (sigtype == SIGINT)
	{
		write(1, "\rminishell-2.0$   \n", 20);
		rl_on_new_line();
		rl_redisplay();
	}
}

int ft_putchar(char *c)
{
	write (1, &c, 1);
}

int	main(int argc, char *argv[], char **env)
{
	// int fd = open(ttyname(1), O_RDWR);
	// printf("%i %s %i", isatty(1), ttyname(1), ttyslot());
	// ft_putstr_fd("df", 1);
	// char buf[200];
	// read(fd, buf, 10);
	

	char	*str;
	t_cmds	*cmds;

	signal(SIGINT, signalg);
	if (argc == 2)
	{
		cmds = NULL;
			if (append_list(&cmds))
				return (1);
		cmds = parse(argv[1], cmds, argv[0]);
		return execute(cmds);
	}
	while (1)
	{
		str = readline("minishell-2.0$ ");
		if (str == NULL)
		{
			write(1, "\033[A\rminishell-2.0$ exit\n", 25);
			exit(1);
		}
		if (!check_input(str))
		{
			cmds = NULL;
			if (append_list(&cmds))
				return (1);
			cmds = parse(str, cmds, argv[0]);
			if (!cmds)
				return (1);
			execute(cmds);
			clear_list(cmds, 0);
		}
		else
			ft_putstr_fd("help", 1);
		add_history(str);
		free(str);
	}
	return (0);
	(void)argc;
	(void)argv;
	(void)env;
}
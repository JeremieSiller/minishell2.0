/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:12 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/27 00:04:23 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <utilities.h>
#include <execute.h>

int	main(int argc, char *argv[], char **env)
{

	char	*str;
	t_cmds	*cmds;

	if (argc == 2)
	{
		cmds = NULL;
			if (append_list(&cmds))
				return (1);
		cmds = parse(argv[1], cmds, argv[0]);
		return execute(cmds, 0);
	}
	while (1)
	{
		str = readline("$>");
		if (!check_input(str))
		{
			cmds = NULL;
			if (append_list(&cmds))
				return (1);
			cmds = parse(str, cmds, argv[0]);
			if (!cmds)
				return (1);
			execute(cmds, 0);
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
	(void)str;
}
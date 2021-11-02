/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:12 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/02 12:53:52 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <utilities.h>
#include <execute.h>
#include <signals.h>
#include <env.h>

int	main(int argc, char *argv[], char **env)
{
	t_cmds	*cmds;
	char		*str;

	if (read_env(env))
		ft_putstr_fd("minishell: env: got an error when trying to create the env\n", 2);
	signal(SIGQUIT, SIG_IGN);
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
		signal(SIGINT, gsignal_ctlc);
		changetermios(false);
		str = readline("minishell-2.0$ \x1b[s");
		if (str == NULL && write(1, "\x1b[uexit\n", 9) && !changetermios(true))
			exit(1);
		if (!check_input(str))
		{
			cmds = NULL;
			if (append_list(&cmds))
				return (1);
			cmds = parse(str, cmds, argv[0]);
			if (!cmds)
				return (1);
			if (find_last(cmds)->cmd == NULL)
				cmds = delete_node(find_last(cmds));
			cmds = find_listhead(cmds);
			execute(cmds);
			clear_list(cmds, 0);
		}
		else
			ft_putstr_fd("help", 1);
		add_history(str);
		free(str);
	}
	return (0);
	(void)env;
}
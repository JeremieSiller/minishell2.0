/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:12 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/26 20:46:58 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <utilities.h>


int	main(int argc, char *argv[], char **env)
{

	char	*str;
	t_cmds	*cmds;
	t_cmds	*head;

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
			head = cmds;
			while (cmds)
			{
				int i = 0;
				while (cmds->cmd && cmds->cmd[i])
				{
					ft_putendl_fd(cmds->cmd[i], 1);
					i++;
				}
				if (cmds->in_dir)
					ft_putendl_fd(cmds->in_dir->path, 1);
				ft_putendl_fd("", 1);
				cmds = cmds->next;
			}
			clear_list(head, 0);
		}
		else
			ft_putstr_fd("help", 1);
		free(str);
	}
	return (0);
	(void)argc;
	(void)argv;
	(void)env;
	(void)str;
}
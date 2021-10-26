/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:12 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/26 03:43:01 by nschumac         ###   ########.fr       */
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
		str = readline(">>");
		cmds = NULL;
		if (append_list(&cmds))
			return (1);
		cmds = parse(str, cmds);
		if (!cmds || (find_last(cmds)->cmd == NULL && find_last(cmds)->previous->operators != OPERATORS_NONE)
			 || (find_last(cmds)->cmd == NULL && find_last(cmds)->previous->write != false))
		{
			ft_putstr_fd("wrong usage\n", 2);
			return (1);
		}
		head = cmds;
		while (cmds)
		{
			int i = 0;
			while (cmds->cmd && cmds->cmd[i])
			{
				ft_putendl_fd(cmds->cmd[i], 1);
				i++;
			}
			ft_putendl_fd("", 1);
			cmds = cmds->next;
		}
		if (cmds && cmds->in_dir)
		{
			ft_putendl_fd(cmds->in_dir->path, 1);
		}
		clear_list(head, 0);
		free(str);
	}
		

	// t_cmds *list = parse(str);



	// while (list)
	// {
		
	// 	list = list->next;
	// }

	return (0);
	(void)argc;
	(void)argv;
	(void)env;
	(void)str;
}
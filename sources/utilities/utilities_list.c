/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:35:27 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/25 22:36:47 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utilities.h>

int	clear_list(t_cmds *node, int ret)
{
	t_cmds	*buf;
	int		cnt;

	while (node->previous != NULL)
		node = node->previous;
	while (node)	
	{
		buf = node->next;
		if (node->cmd)
		{
			cnt = 0;
			while (++cnt && node->cmd && node->cmd[cnt - 1])
				free(node->cmd[cnt - 1]);
			free(node->cmd);
		}
		if (node->in_dir)
			free(node->in_dir);
		if (node->out_dir)
			free(node->out_dir);
		node = buf;
	}
	return (ret);
}

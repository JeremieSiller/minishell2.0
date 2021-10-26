/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:35:27 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/26 02:44:07 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utilities.h>

static void	free_node(t_cmds *node)
{
	int	cnt;

	if (node->cmd)
	{
		cnt = 0;
		while (++cnt && node->cmd[cnt - 1])
			free(node->cmd[cnt - 1]);
		free(node->cmd);
	}
	
	if (node->in_dir)
		free(node->in_dir);
	if (node->out_dir)
		free(node->out_dir);
}

int	clear_list(t_cmds *node, int ret)
{
	t_cmds	*buf;

	while (node->previous != NULL)
		node = node->previous;
	while (node)	
	{
		buf = node->next;
		free_node(node);
		node = buf;
	}
	return (ret);
}

int	append_list(t_cmds **node)
{
	t_cmds	*buf;

	while (*node && (*node)->next)
		*node = (*node)->next;
	buf = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
	if (!buf)
		return (1);
	if (!(*node))
	{
		*node = buf;
		return (0);
	}
	(*node)->next = buf;
	buf->previous = *node;
	*node = buf;
	return (0);
}

t_cmds	*delete_node(t_cmds *node)
{
	t_cmds	*ret;

	if (node->next)
	{
		node->next->previous = NULL;
		ret = node->next;	
		if (node->previous)
		{
			node->previous->next = node->next;
			node->next->previous = node->previous;
		}
	}
	else if (node->previous)
	{
		node->previous->next = NULL;
		ret = node->previous;
	}
	else
		ret = NULL;
	free_node(node);
	return (ret);
}

t_cmds	*find_listhead(t_cmds *node)
{
	while (node->previous)
		node = node->previous;
	return (node);
}
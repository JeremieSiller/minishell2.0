/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_list_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:30:47 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/04 20:54:35 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utilities.h>

t_cmds	*find_last(t_cmds *node)
{
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_cmds	*find_listhead(t_cmds *node)
{
	while (node && node->previous)
		node = node->previous;
	return (node);
}

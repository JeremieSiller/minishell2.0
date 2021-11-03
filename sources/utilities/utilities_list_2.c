/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_list_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:30:47 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/03 21:34:29 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utilities.h>

t_cmds	*find_last(t_cmds *node)
{
	while (node->next != NULL)
		node = node->next;
	return (node);
}

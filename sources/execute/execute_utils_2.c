/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:01:02 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/28 20:07:33 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

void	check_operators(t_cmds **data, t_execute *exec)
{
	if ((*data) && (*data)->previous->operators == OPERATORS_AND && exec->exit != 0)
	{
		while ((*data) && ((*data)->previous->operators != OPERATORS_OR))
			(*data) = (*data)->next;
	}
	if ((*data) && (*data)->previous->operators == OPERATORS_OR && exec->exit == 0)
	{
		while ((*data) && ((*data)->previous->operators != OPERATORS_AND))
			(*data) = (*data)->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:04 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/25 22:57:45 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <minishell.h>

int		clear_list(t_cmds *node);
int		append_list(t_cmds *node);
t_cmds	*delete_node(t_cmds *node);

#endif
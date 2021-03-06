/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:04 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/03 15:58:49 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <minishell.h>

/*
** list functions
*/

int		clear_list(t_cmds *node, int ret);
int		append_list(t_cmds **node);
t_cmds	*delete_node(t_cmds *node);
t_cmds	*find_listhead(t_cmds *node);
t_cmds	*find_last(t_cmds *node);

/*
** list functions
*/

/*
** string functions
*/

int		char_append(char **str, char c);
int		dstring_append(char ***org, char *str);
int		string_append(char **org, char *str);
int		strrlen(char *str);
int		darr_size(char **str);

/*
** string functions
*/

/*
** env suff
*/

char	*get_env_value(char *str);
int		free_env(void);

#endif
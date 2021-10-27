/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:49:22 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/27 21:33:53 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# pragma once

# include <minishell.h>

typedef struct s_builtins
{
	char	*name;
	int		(*func)(char **argv);
}	t_builtins;

int	bt_echo(char **argv);
int	bt_cd(char **argv);
int	bt_env(char **argv);
int	bt_exit(char **argv);
int	bt_export(char **argv);
int	bt_unset(char **argv);
int	bt_pwd(char **argv);
#endif
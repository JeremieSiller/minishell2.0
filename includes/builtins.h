/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:49:22 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/27 21:09:48 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_h
# define BUILTINS_H

# pragma once

# include <minishell.h>

typedef struct s_builtins
{
	char	*name;
	(*func)(char **argv);
}	t_builtins;
int	echo(char **argv);


#endif
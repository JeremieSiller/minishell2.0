/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:22:45 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/28 17:56:26 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bt_exit(char **argv)
{
	ft_putstr_fd("exit\n", 1);
	argv++;
	if (!*argv)
		exit(0);
	exit(ft_atoi(*argv));
}
// need to handle errors (too many arguements/ non numeric arguements)
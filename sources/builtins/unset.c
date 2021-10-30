/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:24:29 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/29 14:08:03 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>

int	bt_unset(char **argv)
{
	printf("%s\n", argv[0]);
	printf("%s\n", argv[1]);
	if (argv && argv[0] && argv[1])
		rm_env(argv[1]);
	return (0);
	(void)argv;
}

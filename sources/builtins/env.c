/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:22:14 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/29 13:28:16 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bt_env(char **argv)
{
	int	i;

	i = 0;
	if (!g_ourenv.env)
	{
		ft_putstr_fd("minishell: env: env is empty\n", 2);
		return (1);
	}
	while (g_ourenv.env[i])
	{
		printf("%s\n", g_ourenv.env[i]);
		i++;
	}
	return (0);
	(void)argv;
}

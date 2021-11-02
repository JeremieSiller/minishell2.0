/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:24:29 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/02 12:19:30 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <utilities.h>
#include <env.h>

static char	set_newenv(char *env)
{
	char	**new_env;
	int		c[2];

	ft_bzero(c, 2 * sizeof(int));
	c[1] = ft_strlen(env);
	new_env = NULL;
	while (++c[0] && g_ourenv.env[c[0] - 1])
	{
		if (!ft_strncmp(g_ourenv.env[c[0] - 1], env, c[1])
			&& g_ourenv.env[c[0] - 1][c[1]] == '=')
			free(g_ourenv.env[c[0] - 1]);
		else
			if (dstring_append(&new_env, g_ourenv.env[c[0] - 1]))
				return (1);
	}
	free(g_ourenv.env);
	g_ourenv.env = new_env;
	return (0);
}

int	bt_unset(char **argv)
{
	int	i;

	if (darr_size(argv) >= 2)
	{
		i = 1;
		while (argv[i])
		{
			if (set_newenv(argv[i]))
				return (1);
		}
	}
	return (0);
}

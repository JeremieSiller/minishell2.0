/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:03:26 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/30 18:19:58 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	free_env()
{
	int	i;

	i = 0;
	while (g_ourenv.env && g_ourenv.env[i])
		free(g_ourenv.env[i]);
	if (g_ourenv.env)
		free(g_ourenv.env);
	g_ourenv.env = NULL;
	return (0);
}

int	read_env(char **env)
{
	int	i;

	g_ourenv.env = ft_calloc(get_env_size(env) + 1, sizeof(*g_ourenv.env));
	if (!g_ourenv.env)
		return (1);
	i = 0;
	while (env && env[i])
	{
		g_ourenv.env[i] = ft_strdup(env[i]);
		if (!g_ourenv.env[i])
			return (1 + free_env());
		i++;
	}
	g_ourenv.exit_status = 0;
	return (0);
}

/*
** reallocates env so str fits in. Does not check if str is a correct env string
** str should not be allocated. Env will point to str!
*/
int	add_env(char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(get_env_size(g_ourenv.env) + 2, sizeof(*g_ourenv.env));
	if (!tmp)
		return (1);
	while (g_ourenv.env && g_ourenv.env[i])
	{
		tmp[i] = g_ourenv.env[i];
		i++;
	}
	tmp[i] = str;
	if (g_ourenv.env)
		free(g_ourenv.env);
	g_ourenv.env = tmp;
	return (0);
}

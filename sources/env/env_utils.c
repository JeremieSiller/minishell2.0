/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:03:26 by jsiller           #+#    #+#             */
/*   Updated: 2022/03/08 15:16:30 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_value(char *str)
{
	int	i;

	i = 0;
	while (g_ourenv.env && g_ourenv.env[i] && str)
	{
		if (!ft_strncmp(g_ourenv.env[i], str,
				ft_strlen(str)))
			return (ft_strchr(g_ourenv.env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

static int	get_env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	free_env(void)
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

	g_ourenv.env = ft_calloc(get_env_size(env) + 2, sizeof(char *));
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

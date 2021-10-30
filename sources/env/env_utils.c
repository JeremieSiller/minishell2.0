/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:03:26 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/29 14:08:35 by jsiller          ###   ########.fr       */
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

int	read_env(char **env)
{
	int	i;

	g_ourenv.env = ft_calloc(get_env_size(env) + 1, sizeof(*g_ourenv.env));
	if (!g_ourenv.env)
		return (1);
	i = 0;
	while (env && env[i])
	{
		g_ourenv.env[i] = env[i];
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
	while (g_ourenv.env[i])
	{
		tmp[i] = g_ourenv.env[i];
		i++;
	}
	tmp[i] = str;
	free(g_ourenv.env);
	g_ourenv.env = tmp;
	return (0);
}

int	rm_env(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;

	i = 0;
	while (g_ourenv.env && g_ourenv.env[i])
	{
		if (!strncmp(str, g_ourenv.env[i], ft_strlen(str)))
			break;
		i++;
	}
	if (i == get_env_size(g_ourenv.env))
		return (0);
	tmp = ft_calloc(sizeof(char *), get_env_size(g_ourenv.env));
	if (!tmp)
	{
		perror("minishell: env");
		return (1);
	}
	j = 0;
	k = 0;
	while (g_ourenv.env[j])
	{
		if (j == i)
			j++;
		tmp[k] = g_ourenv.env[j];
		k++;
		j++;
	}
	free(g_ourenv.env[j]);
	g_ourenv.env = tmp;
	return (0);
}

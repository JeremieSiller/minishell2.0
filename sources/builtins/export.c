/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:23:47 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/03 15:39:46 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <utilities.h>

/*
** checks if the new env is already in the list
** if it is it frees and changes it to the new one
*/
static char	oldenvs(char *env)
{
	char	*chr;
	int		c;

	chr = ft_strchr(env, '=');
	c = 0;
	while (g_ourenv.env[c])
	{
		if (!ft_strncmp(g_ourenv.env[c], env, (chr - env) + 1))
		{
			free(g_ourenv.env[c]);
			g_ourenv.env[c] = env;
			return (0);
		}
		c++;
	}
	return (1);
}

/*
** prints all exported variables
*/
static int	printexportnovars()
{
	int		i;
	char	*buf;

	i = 0;
	while (g_ourenv.env[i])
	{
		buf = ft_strchr(g_ourenv.env[i], '=');
		printf("declare -x %.*s=\"%s\"\n",
			(int)(buf - g_ourenv.env[i]), g_ourenv.env[i], buf + 1);
		i++;
	}
	return (0);
}

static int	doexport(char **argv)
{
	int		i;
	char	*buf;

	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			buf = ft_strdup(argv[i]);
			if (!buf)
				return (1);
			if (oldenvs(buf))
				if (dstring_append(&g_ourenv.env, buf))
					return (1);
		}
		i++;
	}
	return (0);
}

int	bt_export(char **argv)
{
	if (darr_size(argv) < 1)
		return (0);
	else if (darr_size(argv) == 1)
		return (printexportnovars());
	else if (darr_size(argv) >= 2)	
		return (doexport(argv));
	return (1);
}

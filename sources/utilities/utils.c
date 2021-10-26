/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 00:15:31 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/27 00:21:36 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*get_env_val(char **env, char *str)
{
	char	*chr;
	int		c;
	int		l;

	l = ft_strlen(str);
	c = 0;
	while (env[c])
	{
		chr = ft_strchr(env[c], '=');
		if (!strncmp(env[c], str, l) && env[c][l] == '=')
		{
			return (chr + 1);
		}
		c++;
	}
	return ("");
}

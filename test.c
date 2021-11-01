/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:57 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/01 16:36:03 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libft.h>

static int	free_path(char **path, int returnvalue)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (returnvalue);
}

int	find_command(char *arg, char **str, char **env)
{
	char		**path;
	int			i;
	char		*tmp;
	struct stat	buf;

	path = ft_split("/Users/jsiller/.brew/bin:/Users/jsiller/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/jsiller/.brew/bin", ':');
	if (!path)
		return (1);
	i = 0;
	while (path[i] && ft_strncmp(arg, "./", 2) && arg[0] != '/')
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (free_path(path, 1));
		free(path[i]);
		path[i] = tmp;
		*str = ft_strjoin(path[i], arg);
		if (!*str)
			return (free_path(path, 1));
		if (stat(*str, &buf) == 0)
			return (free_path(path, 0));
		free(*str);
		i++;
	}
	*str = arg;
	return (0);
	(void)env;
}

int	main(void)
{
	char *arg = "test";
	char *str;
	find_command(arg, &str, NULL);
	//free (str);
}
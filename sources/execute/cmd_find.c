/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:37:36 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/04 18:49:58 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <utilities.h>
#include <minishell.h>

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

static int	not_found_404(char *arg, char **path, char **str)
{
	if (path)
		free_path(path, 0);
	*str = arg;
	if (arg[0] == '/' || !ft_strncmp(arg, "./", 2))
		return (0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": cmd not found", 2);
	return (2);
}

/*
** ft_find_command checks if the command args is existing and str
** the correct path in str. Str is allocated and needs to be freed.
*/
int	find_command(char *arg, char **str, char __attribute__((unused)) **env)
{
	char		**path;
	int			i;
	char		*tmp;
	struct stat	buf;

	path = ft_split(get_env_value("PATH"), ':');
	i = 0;
	while (path && path[i] && ft_strncmp(arg, "./", 2) && arg[0] != '/' && arg[0])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (free_path(path, 1));
		free(path[i]);
		path[i] = tmp;
		*str = ft_strjoin(path[i], arg);
		if (!*str)
			return (free_path(path, 1));
		if (stat(*str, &buf) == 0 && access(*str, X_OK) == 0)
			return (free_path(path, 0));
		free(*str);
		i++;
	}
	return (not_found_404(arg, path, str));
}

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

/*
** ft_find_command checks if the command args is existing and str
** the correct path in str. Str is allocated and needs to be freed.
*/

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
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

// static int	ft_command_not_found(t_data *data, char **path, char *arg)
// {
// 	ft_putstr_fd(ERROR_MSG, 2);
// 	ft_putstr_fd(arg, 2);
// 	ft_putstr_fd(": command not found\n", 2);
// 	dup2(data->s_stdin, 0);
// 	dup2(data->s_stdout, 1);
// 	return (ft_free_path(path, CMD_NOTFOUND));
// }

// static int	ft_check_if_path_is_given(char **path, char *arg,
// 	char **str, t_data *data)
// {
// 	if (arg[0] == '/' || (arg[0] == '.' && arg[1] == '/'))
// 	{
// 		*str = ft_strdup(arg);
// 		if (!*str)
// 			return (ft_free_path(path, 1));
// 		return (ft_free_path(path, 0));
// 	}
// 	return (ft_command_not_found(data, path, arg));
// }

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

	path = ft_split(get_env_val(env, "PATH"), ':');
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
}
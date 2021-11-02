/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:25:38 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/02 12:52:16 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <execute.h>

static int	here_doc(t_cmds *data, t_execute *exec)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	while (data->in_dir[i])
	{
		if (data->in_dir[i]->type == 1)
		{
			fd = open("___here_doc___", O_RDWR);
			if (fd == -1)
			{
				perror("minishell: here_doc");
				return (1);
			}
			str = readline("> ");
			while (str && strncmp(data->in_dir[i]->path, str, ft_strlen(data->in_dir[i]->path) + 1))
			{
				write(fd, str, ft_strlen(str));
				free(str);
			}
			free(str);
			if (dup2(fd, 0) == -1)
			{
				perror("minishell");
				close(fd);
				return (1);
			}
			close(fd);
		}
		i++;
	}
	return (0);
}

static int	out_directions(t_cmds *data, t_execute *exec)
{
	int	i;
	int	fd;

	i = 0;
	while (data->out_dir && data->out_dir[i])
	{
		if (data->out_dir[i]->type == 0)
			fd = open(data->out_dir[i]->path, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(data->out_dir[i]->path, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(data->out_dir[i]->path);
			exec->exit = 1;
			return (1);
		}
		if (dup2(fd, 1) == -1);
		{
			perror("minishell");
			close(fd);
			return (1);
		}
		close(fd);
		i++;
	}
	return (0);
}

static int	in_directions(t_cmds *data, t_execute *exec)
{
	int	i;
	int	fd;

	i = 0;
	while (data->in_dir && data->in_dir[i])
	{
		if (data->in_dir[i]->type == 0)
		{
			fd = open(data->in_dir[i]->path, O_RDONLY);
			if (fd == -1)
			{
				perror(data->in_dir[i]->path);
				exec->exit = 1;
				return (1);
			}
			if (dup2(fd, 0) == -1)
			{
				close(fd);
				return (1);
			}
			close(fd);
		}
		i++;
	}
}

int	redirect(t_cmds *data, t_execute *exec)
{
	if (in_directions(data, exec) == 1)
		return (1);
	return (out_directions(data, exec));
}
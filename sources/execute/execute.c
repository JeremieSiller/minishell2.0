/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 00:13:31 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/01 20:58:10 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <execute.h>
#include <signals.h>
#include <sys/errno.h>
#include <utilities.h>

extern char	**environ;

static int	check_cmd(t_execute *exec, t_cmds *data, char **str)
{
	int	ret;

	ret = find_command(data->cmd[0], str, environ);
	if (ret == 1)
		return (execute_child_erros(1, exec, data));
	collect_garbage(exec);
	if (ret == 2)
	{
		clear_list(data, 0);
		return (127);
	}
	return (0);
}

static int	child(t_execute *exec, t_cmds *data)
{
	char	*str;
	int		ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	changetermios(true);
	if (data->read == 1 && dup2(exec->s_fd, 0) == -1)
		return (execute_child_erros(1, exec, data));
	if (data->write == 1 && dup2(exec->fd[1], 1) == -1)
		return (execute_child_erros(1, exec, data));
	if (check_builtin(data->cmd, exec) == 0)
	{
		collect_garbage(exec);
		return (exec->exit);
	}
	ret = check_cmd(exec, data, &str);
	if (ret != 0)
		return (ret);
	execve(str, data->cmd, environ);
	perror(data->cmd[0]);
	return (126);
}

static void	parent(t_execute *exec, t_cmds *data)
{
	if (exec->s_fd != -1)
		close(exec->s_fd);
	exec->s_fd = -1;
	if (exec->fd[1] != -1)
		close(exec->fd[1]);
	exec->fd[1] = -1;
	exec->s_fd = exec->fd[0];
	exec->fd[0] = -1;
	if (data->operators != OPERATORS_NONE)
	{
		ft_lstiter(exec->lst, ft_wait);
		exec->exit = ((t_pid *)ft_lstlast(exec->lst)->content)->exit;
	}
}

int	create_childs(t_cmds *data, t_execute *exec)
{
	t_pid			*pid;
	t_list			*tmp;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_DFL);
	pid = malloc(sizeof(*pid));
	if (!pid)
		return (execute_errors(MALLOC_ERR, exec));
	*pid = (t_pid){};
	tmp = ft_lstnew(pid);
	if (!tmp)
		free(pid);
	if (!tmp)
		return (execute_errors(MALLOC_ERR, exec));
	ft_lstadd_back(&(exec->lst), tmp);
	if (data->write == 1 && pipe(exec->fd) == -1)
		return (execute_errors(PIPE_ERR, exec));
	pid ->pid = fork();
	if (pid->pid == -1)
		return (execute_errors(FORK_ERR, exec));
	if (pid->pid == 0)
		exit(child(exec, data));
	else
		parent(exec, data);
	return (0);
}

/*
** execute gets a list of arguements and executes them
** scope always starts with 0 and only gets increased 
** incase of an recursive call
*/
unsigned char	execute(t_cmds *data)
{
	t_execute		exec;

	exec = (t_execute){};
	exec.s_fd = -1;
	exec.fd[0] = -1;
	exec.fd[1] = -1;
	exec.lst = 0;
	while (data != 0)
	{
		if (data->write == 1 || data->read == 1
			|| (data->write == 0 && data->read == 0
				&& check_builtin(data->cmd, &exec) == 1))
		{
			if (create_childs(data, &exec) != 0)
				return (exec.exit);
		}
		data = data->next;
		check_operators(&data, &exec);
	}
	ft_lstiter(exec.lst, ft_wait);
	if (exec.lst)
		exec.exit = ((t_pid *)ft_lstlast(exec.lst)->content)->exit;
	collect_garbage(&exec);
	return (exec.exit);
}

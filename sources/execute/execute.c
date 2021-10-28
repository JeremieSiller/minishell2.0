/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 00:13:31 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/28 20:30:33 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <execute.h>
#include <signals.h>
#include <sys/errno.h>

extern char **environ;

static void	child(t_execute *exec, t_cmds *data)
{
	int	ret;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	changetermios(true);
	char	*str;
	if (data->read == 1 && dup2(exec->s_fd, 0) == -1)
	{
		ft_putstr_fd("Dup error\n", 2);
		return ;
	}
	if (data->write == 1 && dup2(exec->fd[1], 1) == -1)
	{
		ft_putstr_fd("Dup error\n", 2);
		return ;
	}
	if (data->write == 0 && dup2(exec->s_out, 1) == -1)
	{
		ft_putstr_fd("Dup error\n", 2);
		return ;
	}
	if (data->read == 0 && dup2(exec->s_in, 0) == -1)
	{
		ft_putstr_fd("Dup error\n", 2);
		return ;
	}
	close(exec->fd[0]);
	close(exec->fd[1]);
	close(exec->s_fd);
	ret = check_builtin(data->cmd);
	if (ret != -1)
		exit(ret);
	find_command(data->cmd[0], &str, environ);
	ft_lstclear(&(exec->lst), free);
	execve(str, data->cmd, environ);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": cmd not found", 2);
	exit(127);
}

static void	parent(t_execute *exec, t_cmds *data)
{
	if (exec->s_fd != -1)
		close(exec->s_fd);
	close(exec->fd[1]);
	exec->s_fd = dup(exec->fd[0]);
	close(exec->fd[0]);
	if (data->operators != OPERATORS_NONE)
	{
		ft_lstiter(exec->lst, ft_wait);
		exec->exit = ((t_pid *)ft_lstlast(exec->lst)->content)->exit;
	}
}

void	exec_main(t_cmds *data, t_execute *exec)
{
	int		ret;
	int		id;
	char	*str;

	ret = check_builtin(data->cmd);
	if (ret != -1)
	{
		exec->exit = ret;
		return ;
	}
	signal(SIGINT, SIG_IGN);
	if (!our_minishell(data->cmd[0]))
		signal(SIGINT, fsignal_ctlc);
	id = fork();
					if (id == -1)
					{
						ft_putstr_fd("fork eror\n", 2);
						return ;
					}
	if (id == 0)
	{
		find_command(data->cmd[0], &str, environ);
		ft_lstclear(&(exec->lst), free);
		execve(str, data->cmd, environ);
		if (errno == 2)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd(": cmd not found", 2);
			exit(127);
		}
		perror(data->cmd[0]);
		exit(errno);
	}
	else
	{
		wait(&ret);
		if (WIFEXITED(ret))
			exec->exit = WEXITSTATUS(ret);
	}
}

int	create_childs(t_cmds *data, t_execute *exec)
{
	t_pid			*pid;
	t_list			*tmp;

	pid = malloc(sizeof(*pid));
	if (!pid)
		return (execute_errors(MALLOC_ERR, exec));
	if (pipe(exec->fd) == -1)
		return (execute_errors(PIPE_ERR, exec));
	pid ->pid = fork();
	if (pid->pid == -1)
		return (execute_errors(FORK_ERR, exec));
	if (pid->pid == 0)
		child(exec, data);
	else 
	{
		tmp = ft_lstnew(pid);
		if (!tmp)
			return (execute_errors(MALLOC_ERR, exec));
		ft_lstadd_back(&(exec->lst), tmp);
		parent(exec, data);
	}
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
	int				ret;
	if (!data)
		return (0);
	ft_memset(&exec, 0, sizeof(exec));
	exec.s_in = dup(0);
	exec.s_out = dup(1);
	while (data != 0)
	{
		if (data->write == 0 && data->read == 0)
			exec_main(data, &exec);
		else 
		{
			ret = create_childs(data, &exec);
			if (ret != 0)
				return (ret);
		}
		data = data->next;
		check_operators(&data, &exec);
	}
	collect_garbage(&exec);
	return (exec.exit);
}

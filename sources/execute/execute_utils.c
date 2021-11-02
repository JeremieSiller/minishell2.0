/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:03:52 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/31 19:02:28 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <execute.h>
#include <builtins.h>
#include <sys/wait.h>
#include <utilities.h>

static const t_builtins	g_built_cmd[] = {
	{"echo", &bt_echo},
	{"cd", &bt_cd},
	{"pwd", &bt_pwd},
	{"export", &bt_export},
	{"unset", &bt_unset},
	{"env", &bt_env},
	{"exit", &bt_exit},
	{"false", &bt_false},
	{"true", &bt_true},
	{NULL, NULL}
};

void	ft_wait(void *pid)
{
	waitpid(((t_pid *)pid)->pid, &((t_pid *)pid)->exit, 0);
	if (WIFEXITED(((t_pid *)pid)->exit))
		((t_pid *)pid)->exit = WEXITSTATUS(((t_pid *)pid)->exit);
}

int	check_builtin(char **cmd, t_execute *exec)
{
	int	i;

	i = 0;
	while (g_built_cmd[i].name)
	{
		if (!ft_strncmp(cmd[0], g_built_cmd[i].name,
				ft_strlen(g_built_cmd[i].name) + 1))
		{
			exec->exit = g_built_cmd[i].func(cmd); 
			return (0);
		}
		i++;
	}
	return (1);
}

void	collect_garbage(t_execute *exec)
{
	if (exec->s_fd != -1)
	{
		close(exec->s_fd);
		exec->s_fd = -1;
	}
	if (exec->fd[0] != -1)
	{
		close(exec->fd[0]);
		exec->fd[0] = -1;
	}
	if (exec->fd[1] != -1)
	{
		close(exec->fd[1]);
		exec->fd[1] = -1;
	}
	ft_lstiter(exec->lst, ft_wait);
	if (exec->lst)
		exec->exit = ((t_pid *)ft_lstlast(exec->lst)->content)->exit;
	ft_lstclear(&(exec->lst), free);
}

int	execute_errors(int ret, t_execute *exec)
{
	perror("minishell");
	collect_garbage(exec);
	exec->exit = ret;
	return (ret);
}

int	execute_child_erros(int ret, t_execute *exec, t_cmds *data)
{
	perror("minishell");
	collect_garbage(exec);
	clear_list(data, 0);
	data = 0;
	return (ret);
}

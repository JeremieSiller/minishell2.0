/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:03:52 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/28 17:30:51 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <execute.h>
#include <builtins.h>

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

int	check_builtin(char **cmd)
{
	int	i;

	i = 0;
	while (g_built_cmd[i].name)
	{
		if (!ft_strncmp(cmd[0], g_built_cmd[i].name,
				ft_strlen(g_built_cmd[i].name) + 1))
		{
			return (g_built_cmd[i].func(cmd));
		}
		i++;
	}
	return (-1);
}

void	collect_garbage(t_execute *exec)
{
	close(exec->s_fd);
	close(exec->s_in);
	close(exec->s_out);
	close(exec->fd[0]);
	close(exec->fd[1]);
	ft_lstiter(exec->lst, ft_wait);
	if (exec->lst)
		exec->exit = ((t_pid *)ft_lstlast(exec->lst)->content)->exit;
	ft_lstclear(&(exec->lst), free);
}

int	execute_errors(int ret, t_execute *exec)
{
	perror("minishell");
	collect_garbage(exec);
	return (ret);
}

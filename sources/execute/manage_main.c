/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:07:41 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/05 16:07:58 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>
#include <builtins.h>
#include <signals.h>

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

/*
** checks if cmd is a builtin. returns 1 if it is a builtin 0 if not
*/
int	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (g_built_cmd[i].name)
	{
		if (!ft_strncmp(cmd, g_built_cmd[i].name,
				ft_strlen(g_built_cmd[i].name) + 1))
			return (1);
		i++;
	}
	return (0);
}

/*
** safes stdin and stdout if redirections are given
** returns 1 on error
*/
static int	safe_std(t_execute *exec, t_cmds *cmd)
{
	if (cmd->in_dir)
	{
		exec->s_in = dup(0);
		if (exec->s_in == -1)
		{
			perror("minishell");
			return (1);
		}
	}
	if (cmd->out_dir)
	{
		exec->s_out = dup(1);
		if (exec->s_out == -1)
		{
			close(exec->s_in);
			perror("minishell");
			return (1);
		}
	}
	return (0);
}

/*
** resets stdin and stdout FD
** returns 1 on error
*/
static int	reset_to_std(t_execute *exec, t_cmds *cmd)
{
	if (cmd->in_dir)
	{
		if (dup2(exec->s_in, 0) == -1)
		{
			close(exec->s_in);
			close(exec->s_out);
			return (1);
		}
		close(exec->s_in);
	}
	if (cmd->out_dir)
	{
		if (dup2(exec->s_out, 1) == -1)
		{
			close(exec->s_out);
			return (1);
		}
		close(exec->s_out);
	}
	return (0);
}

/*
** executes builtins in main
** returns 1 on error
*/
int	exec_in_main(t_execute *exec, t_cmds *cmd)
{
	if (safe_std(exec, cmd) == 1)
		return (1);
	signal(SIGINT, heredoc_ctlc);
	if (redirect(cmd, exec) == 1)
	{
		reset_to_std(exec, cmd);
		return (1);
	}
	check_builtin(cmd, exec);
	if (reset_to_std(exec, cmd) == 1)
		return (1);
	return (exec->exit);
}

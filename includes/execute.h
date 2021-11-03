/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:05:32 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/03 13:52:11 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <libft.h>
# include <minishell.h>
# include <signal.h>

# define PIPE_ERR 2
# define MALLOC_ERR 3
# define FORK_ERR 4

typedef struct s_execute
{
	t_list		*lst;
	int			s_fd;
	int			fd[2];
	int			exit;
}	t_execute;

typedef struct s_pid
{
	int	pid;
	int	exit;
}	t_pid;

unsigned char	execute(t_cmds *data);
int				find_command(char *arg, char **str, char **env);
void			ft_wait(void *pid);
int				check_builtin(char **cmd, t_execute *exec);
void			collect_garbage(t_execute *exec);
int				execute_errors(int ret, t_execute *exec);
void			check_operators(t_cmds **data, t_execute *exec);
int				execute_child_erros(int ret, t_execute *exec, t_cmds *data);
int				redirect(t_cmds *data, t_execute *exec);
void			update_env(t_cmds *cmds);
#endif
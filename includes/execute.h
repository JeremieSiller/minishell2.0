#ifndef EXECUTE_H
# define EXECUTE_H

#include <libft.h>
#include <minishell.h>

#pragma once

# define PIPE_ERR 2
# define MALLOC_ERR 3
# define FORK_ERR 4

typedef struct	s_execute
{
	t_list		*lst;
	int			s_fd;
	int			fd[2];
	int			s_out;
	int			s_in;
	int			exit;
}	t_execute;

typedef struct	s_pid 
{
	int	pid;
	int	exit;
} t_pid;

unsigned char	execute(t_cmds *data);
int				find_command(char *arg, char **str, char **env);
void			ft_wait(void *pid);
int				check_builtin(char **cmd);
void			collect_garbage(t_execute *exec);
int				execute_errors(int ret, t_execute *exec);

#endif
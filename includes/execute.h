#ifndef EXECUTE_H
# define EXECUTE_H

#include <libft.h>
#include <minishell.h>

#pragma once

unsigned char	execute(t_cmds *data);
int				find_command(char *arg, char **str, char **env);

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

#endif
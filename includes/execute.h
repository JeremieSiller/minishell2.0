#ifndef EXECUTE_H
# define EXECUTE_H

#include <libft.h>
#include <minishell.h>

#pragma once

unsigned char	execute(t_cmds *data, unsigned int scope);

typedef struct	s_execute
{
	t_list		*lst;
	int			s_fd;
	int			fd[2];
	int			s_out;
	int			s_in;
}	t_execute;

int	find_command(char *arg, char **str, char **env);

#endif
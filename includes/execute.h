#ifndef EXECUTE_H
# define EXECUTE_H

#include <libft.h>
#include <minishell.h>

#pragma once

typedef struct	s_execute
{
	t_list		*lst;
	int			s_fd;
	int			fd[2];
	int			s_out;
	int			s_in;
}	t_execute;


#endif
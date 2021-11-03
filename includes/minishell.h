/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:35:59 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/03 21:05:56 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>

# define OPERATORS_NONE 0
# define OPERATORS_OR 1
# define OPERATORS_AND 2

typedef struct s_redirect
{
	bool	type;
	char	*path;
}	t_redirect;

typedef struct s_cmds
{
	char			**cmd;
	bool			read;
	bool			write;
	int				scope;
	int				operators;
	int				exit_status;
	t_redirect		**in_dir;
	t_redirect		**out_dir;
	struct s_cmds	*previous;
	struct s_cmds	*next;
	char			*str;
}	t_cmds;

// char	**g_ourenv;
typedef struct s_variables
{
	char			**env;
	unsigned char	exit_status;
}	t_variables;

t_variables	g_ourenv;

#endif
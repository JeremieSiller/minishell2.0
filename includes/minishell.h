/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:35:59 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/25 23:33:59 by jsiller          ###   ########.fr       */
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
# include <libft.h>

# define ALL 0
# define AND 1
# define OR 2


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
	t_redirect		*in_dir;
	t_redirect		*out_dir;
	struct s_cmds	*previous;
	struct s_cmds	*next;
}	t_cmds;


#endif
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_redirect
{
	bool	type;
	char	*path;
}	t_redirect;
typedef struct s_list
{
	char			**cmd;
	bool			read;
	bool			write;
	int				scope;
	int				operators;
	int				exit_status;
	t_redirect		*in_dir;
	t_redirect		*out_dir;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;


#endif
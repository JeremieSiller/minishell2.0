#include <minishell.h>


static	void	child()
{
	
}

//							todo
unsigned char	execute(t_cmds *data, unsigned int scope)
{
	int				fd[2];
	t_list			*lst;
	int				*pid;
							if (!data)
							{
								ft_putstr_fd("Got a null pointer, something went wrong\n", 2);
								return (1);
							}
	lst = NULL;
	while (data->next)
	{
		pid = malloc(sizeof(int));
							if (!pid)
							{
								ft_putstr_fd("Malloc error\n", 2);
								return (1);
							}
		pid = pipe(fd);
		if (pid == -1)
							return (1);
						
		ft_lstadd_back(&lst, ft_lstnew(pid));
	}
	ft_lstclear(&lst, free);
}

int	main(void)
{
	t_cmds	*head = malloc(sizeof(head));
	head->scope = 0;
	head->operators = ALL;
	head->next		= malloc(sizeof(head));
	head->next->scope		= 1;
	head->next->operators	= AND;
	head->next->next		= malloc(sizeof(head));
	head->next->next->scope = 1;
	head->next->next->next = 0;
	printf("here\n");
	printf("%d\n", get_pids(head, 0));
}
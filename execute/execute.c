#include <minishell.h>
#include <execute.h>

extern char **environ;

static void	child(t_execute *exec, t_cmds *data)
{

	if (data->read == 1 && dup2(exec->s_fd, 0) == -1)
	{
		ft_putstr_fd("Dup error\n", 2);
		return ;
	}
	if (data->write == 1 && dup2(exec->fd[1], 1) == -1)
	{
		ft_putstr_fd("Dup error\n", 2);
		return ;
	}
	if (data->write == 0 && dup2(exec->s_out, 1) == -1)
	{
		ft_putstr_fd("Dup error\n", 2);
		return ;
	}
	if (data->read == 0 && dup2(exec->s_in, 0) == -1)
	{
		ft_putstr_fd("Dup error\n", 2);
		return ;
	}
	close(exec->fd[0]);
	close(exec->fd[1]);
	close(exec->s_fd);
	ft_lstclear(&(exec->lst), free);
	execve(data->cmd[0], data->cmd, environ);
	ft_putstr_fd("some error\n", 2);
	exit(1);
}

static void	parent(t_execute *exec, t_cmds *data)
{
	if (exec->s_fd != -1)
		close(exec->s_fd);
	close(exec->fd[1]);
	exec->s_fd = dup(exec->fd[0]);
	close(exec->fd[0]);
}

void	ft_wait(void *pid)
{
	waitpid(*(int *)pid, 0, 0);
}
/*
** execute gets a list of arguements and executes them
** scope always starts with 0 and only gets increased 
** incase of an recursive call
*/
unsigned char	execute(t_cmds *data, unsigned int scope)
{
	int				*pid;
	t_list			*tmp;
	t_execute		exec;
							if (!data)
							{
								ft_putstr_fd("Got a null pointer, something went wrong\n", 2);
								return (1);
							}
	int status = 0;
	exec.s_fd = -1;
	exec.lst = 0;
	exec.s_in = dup(0);
	exec.s_out = dup(1);
	while (data != 0)
	{
		pid = malloc(sizeof(int));
		*pid = 1;
							if (!pid)
							{
								ft_putstr_fd("Malloc error\n", 2);
								ft_lstclear(&(exec.lst), free);
								return (1);
							}
		if (pipe(exec.fd) == -1)
							{
								ft_putstr_fd("Pipe error\n", 2);
								ft_lstclear(&(exec.lst), free);
								return (1);
							}
		*pid = fork();
							if (*pid == -1)
							{
								ft_putstr_fd("Fork error\n", 2);
								ft_lstclear(&(exec.lst), free);
								close(exec.fd[0]);
								close(exec.fd[1]);
								return (1);
							}
		if (*pid == 0)
		{
			child(&exec, data);
		}
		else 
		{
			tmp = ft_lstnew(pid);
								if (!tmp)
								{
									ft_putstr_fd("Error\n", 2);
									return (1);
								}
			ft_lstadd_back(&(exec.lst), tmp);
			parent(&exec, data);
		}
		data = data->next;
	}
	close(exec.s_fd);
	ft_lstiter(exec.lst, ft_wait);
	ft_lstclear(&exec.lst, free);
	return (0);
}

int	main(void)
{
	char **ls = ft_split("/bin/ls -l", ' ');
	char **cat = ft_split("/usr/bin/grep a", ' ');
	t_cmds	*head = calloc(sizeof(*head), 1);
	//head->scope = 0;
	head->read = 0;
	head->write = 1;
	head->cmd = ls;
	head->next		= calloc(sizeof(*head), 1);
	//head->next->scope		= 0;
	head->next->read = 1;
	head->next->write = 0;
	head->next->cmd = cat;
	head->next->next = 0;
	execute(head, 0);
}
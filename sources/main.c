#include "../includes/minishell.h"
#include "../includes/parser.h"


int	main(int argc, char *argv[], char **env)
{

	char *str = readline(">");

	t_cmds *list = parse(str);



	while (list)
	{
		
		list = list->next;
	}

	return (0);
}
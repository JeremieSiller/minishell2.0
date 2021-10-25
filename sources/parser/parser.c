#include <parser.h>

int	double_qoutes(char *str, int *cnt)
{

}

int	single_qoutes(char *str, int *cnt)
{

}

t_cmds	*parse(char *str)
{	
	int		cnt;
	t_cmds	*head;

	cnt = 0;	
	while (str[cnt])
	{
		if (str[cnt] == '\"' && !double_qoutes(str, &cnt))
			return (NULL);
		


		cnt++;
	}


	return (head);
}



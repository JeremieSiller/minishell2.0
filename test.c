
#include <readline/readline.h>
#include <stdlib.h>

int	main(void)
{
	char *str;
	
	while (1)
	{
		str = readline("> ");
		free(str);
	}
	return(2);
}

#include <utilities.h>

t_cmds	*find_last(t_cmds *node)
{
	while (node->next != NULL)
		node = node->next;
	return (node);
}
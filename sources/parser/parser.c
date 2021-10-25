/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:38:44 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/26 00:57:41 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>

int	parse_variable(char **str, char **strbuf, t_cmds *cur)
{

}

t_cmds	*parse(char *str)
{	
	char	*strbuf;
	t_cmds	*cur;

	while (str && *str)
	{
		if (ft_strchr(ENDSTRING, *str) && parse_endstring(&str, &strbuf, cur))
			return (clear_list(cur, NULL));
		else if (*str == '$' && parse_variable(&str, &strbuf, cur))
			return (clear_list(cur, NULL));
		else if (ft_strchr(ENDCOMMAND, *str) && parse_endcommands(&str, &strbuf, cur))
			return (clear_list(cur, NULL));
		else if (ft_strchr(REDIRECTIONS, *str) && parse_redirections(&str, &strbuf, cur))
			return (clear_list(cur, NULL));
		else if (char_append(&strbuf, *str))
			return (clear_list(cur, NULL));
		str++;
	}
	if (strbuf)
		if(string_append(&cur->cmd, strbuf))
			return (clear_list(cur, NULL));
	return (find_listhead(cur));
}

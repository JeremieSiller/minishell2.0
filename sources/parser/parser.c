/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:38:44 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/04 21:00:54 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>

static int	parse_space(char **strbuf, t_cmds *cur)
{
	if (!(*strbuf))
		return (0);
	if (dstring_append(&cur->cmd, *strbuf))
		return (1);
	*strbuf = NULL;
	return (0);
}

static int	parse_2(char **str, t_cmds *cur, int fc, char **strbuf)
{	
	if (ft_strchr(REDIRECTIONS, **str) && ++fc
		&& parse_redirections(str, strbuf, &cur))
		return (1);
	else if (**str == '*' && ++fc && parse_arsterix(str, strbuf, &cur))
		return (1);
	else if (!fc && char_append(strbuf, **str))
		return (1);
	return (0);
}

t_cmds	*parse(char *str, t_cmds *cur, char *argv)
{	
	char	*strbuf;
	int		fc;

	strbuf = NULL;
	while (str && *(str))
	{
		fc = 0;
		if (ft_strchr(ENDSTRING, *str) && ++fc && parse_qoutes(&str, &strbuf))
			return ((void *)(size_t)clear_list(cur, 0));
		else if (*str == ' ' && ++fc && parse_space(&strbuf, cur))
			return ((void *)(size_t)clear_list(cur, 0));
		else if (ft_strchr(ENDCOMMAND, *str) && ++fc
			&& parse_endcommands(&str, &strbuf, &cur, argv))
			return ((void *)(size_t)clear_list(cur, 0));
		else if (parse_2(&str, cur, fc, &strbuf))
			return ((void *)(size_t)clear_list(cur, 0));
		str++;
	}
	if (strbuf)
		if (dstring_append(&cur->cmd, strbuf))
			return ((void *)(size_t)clear_list(cur, 0));
	return (find_listhead(cur));
}

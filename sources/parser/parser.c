/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:38:44 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/27 00:06:34 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>

static int	parse_space(char **strbuf, t_cmds *cur, int *fc)
{
	*fc = 1;
	if (!(*strbuf))
		return (0);
	if (dstring_append(&cur->cmd, *strbuf))
		return (1);
	*strbuf = NULL;
	return (0);
}

int	check_input(char *str)
{
	int	scope;

	scope = 0;
	if (!str)
		return (1);
	while (*str)
	{
		if (ft_strchr(ENDCOMMAND, *str) && *str != '(')
		{
			str++;
			if ((*(str) == '|' && *(str - 1) == '|') ||
				(*(str) == '&' && *(str - 1) == '&'))
				str++;
			while (*str && *str == ' ')
				str++;
			if ((ft_strchr(ENDCOMMAND, *str) && *str != '(' ) || *str == 0)
				return (1);
			str--;
		}
		else if (ft_strchr(REDIRECTIONS, *str))	
		{
			str++;
			if ((*(str) == '>' && *(str - 1) == '>') ||
				(*(str) == '<' && *(str - 1) == '<'))
				str++;
			while (*str && *str == ' ')
				str++;
			if (ft_strchr(ENDCOMMAND, *str) || ft_strchr(REDIRECTIONS, *str) || *str == 0)
				return (1);	
			str--;
		}
		else if (*str == '(')	
			scope++;
		else if (*str == ')')
			scope--;
		str++;
	}
	if (scope != 0)
		return (1);
	return 0;
}

t_cmds	*parse(char *str, t_cmds *cur, char *argv)
{	
	char	*strbuf;
	int		fc;

	strbuf = NULL;
	while (str && *(str))
	{
		fc = 0;
		if (ft_strchr(ENDSTRING, *str) && parse_qoutes(&str, &strbuf, &fc))
			return ((void *)(size_t)clear_list(cur, 0));
		else if (*str == ' ' && parse_space(&strbuf, cur, &fc))
			return ((void *)(size_t)clear_list(cur, 0));
		else if (ft_strchr(ENDCOMMAND, *str)
			&& parse_endcommands(&str, &strbuf, &cur, &fc, argv))
			return ((void *)(size_t)clear_list(cur, 0));
		else if (ft_strchr(REDIRECTIONS, *str)
			&& parse_redirections(&str, &strbuf, &cur, &fc))
			return ((void *)(size_t)clear_list(cur, 0));
		else if (!fc && char_append(&strbuf, *str))
			return ((void *)(size_t)clear_list(cur, 0));
		str++;
	}
	if (strbuf)
		if(dstring_append(&cur->cmd, strbuf))
			return ((void *)(size_t)clear_list(cur, 0));
	return (find_listhead(cur));
}

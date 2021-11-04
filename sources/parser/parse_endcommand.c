/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_endcommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:51:26 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/04 20:45:05 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>

static int	parse_and(char **str, char **strbuf, t_cmds **cur)
{
	if (*strbuf)
	{
		if (dstring_append(&(*cur)->cmd, *strbuf))
			return (1);
		*strbuf = NULL;
	}
	if ((*cur)->cmd)
		(*cur)->operators = OPERATORS_AND;
	if ((*cur)->cmd && append_list(cur))
		return (1);
	if ((*cur)->previous)
		(*cur)->previous->operators = OPERATORS_AND;
	*str += 1;
	return (0);
}

static int	parse_pipe(char **strbuf, t_cmds **cur)
{
	if (*strbuf)
	{
		if (dstring_append(&(*cur)->cmd, *strbuf))
			return (1);
		*strbuf = NULL;
	}
	if (!(*cur)->cmd)
	{
		if ((*cur)->previous)
			(*cur)->previous->write = true;
		(*cur)->read = true;
	}
	if ((*cur)->cmd)
		(*cur)->write = true;
	if ((*cur)->cmd && append_list(cur))
		return (1);
	(*cur)->read = true;
	return (0);
}

static int	parse_brackets2(char **str, char **buf, t_cmds **cur)
{
	int	scope;

	scope = 0;
	*buf = NULL;
	while (**str && (*(++(*str)) != ')' || scope != 0))
	{
		if (char_append(buf, **str))
			return (1);
		if (**str == '(')
			scope++;
		if (**str == ')')
			scope--;
	}
	if (dstring_append(&(*cur)->cmd, *buf))
		return (1);
	if (append_list(cur))
		return (1);
	return (0);
}

static int	parse_brackets(char **str, char **strbuf, t_cmds **cur, char *argv)
{
	int		scope;
	char	*buf;

	if (*strbuf)
	{
		if (dstring_append(&(*cur)->cmd, *strbuf))
			return (1);
		*strbuf = NULL;
	}
	if ((*cur)->cmd && append_list(cur))
		return (1);
	scope = 0;
	buf = ft_strdup(argv);
	if (!buf)
		return (1);
	if (dstring_append(&(*cur)->cmd, buf))
		return (1);
	return (parse_brackets2(str, &buf, cur));
}

int	parse_endcommands(char **str, char **strbuf, t_cmds **cur, char *argv)
{
	if (**str == '(')
		return (parse_brackets(str, strbuf, cur, argv));
	if (**str == '|' && *(*str + 1) != '|')
		return (parse_pipe(strbuf, cur));
	if (**str == '|')
		return (parse_or(str, strbuf, cur));
	if (**str == '&' && *((*str)++) == '&')
		return (parse_and(str, strbuf, cur));
	else
		return (char_append(strbuf, **str));
}

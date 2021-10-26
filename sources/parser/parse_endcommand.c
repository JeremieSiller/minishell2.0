/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_endcommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:51:26 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/26 02:59:19 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>

// IF TWO OPERATORSA COME AFTER EACH OTHER IT SHOULD CAUSE ERROR
// DO I JUST CREATE A NODE IN THE LIST THAT HAS CMD 0 IF THAT HAPPENS
// THEN YOU JEREMEY COULD CAUSE ERROR

static int	parse_or(char **str, char **strbuf, t_cmds **cur)
{
	if (*strbuf)
	{
		if (dstring_append(&(*cur)->cmd, *strbuf))
			return (1);
		*strbuf = NULL;
	}
	if ((*cur)->cmd)
		(*cur)->operators = OPERATORS_OR;
	if ((*cur)->cmd && append_list(cur))
		return (1);
	if ((*cur)->previous)
		(*cur)->previous->operators = OPERATORS_OR;
	*str += 1;
	return (0);
}

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
	return (0);
}

int	parse_endcommands(char **str, char **strbuf, t_cmds **cur, int *fc)
{
	*fc = 1;
	if (**str == '|' && *(*str + 1) != '|')
		return (parse_pipe(strbuf, cur));
	if (**str == '|')
		return (parse_or(str, strbuf, cur));
	if (**str == '&' && *((*str)++) == '&')
		return (parse_and(str, strbuf, cur));
	else
		return (char_append(strbuf, **str));
}
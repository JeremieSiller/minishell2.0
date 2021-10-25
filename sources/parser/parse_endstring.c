/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_endstring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:51:31 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/26 00:57:09 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int	parse_double(char **str, char **strbuf, t_cmds *cur)
{

}

static int	parse_single(char **str, char **strbuf, t_cmds *cur)
{

}

static int	parse_string(char **str, char **strbuf, t_cmds *cur)
{
	
}

int	parse_endstring(char **str, char **strbuf, t_cmds *cur)
{
	if (*str == '\'')
		return (parse_single(str, strbuf, cur));
	else if (*str == '\"')
		return (parse_double(str, strbuf, cur));
	else
		return (parse_string(str, strbuf, cur));
}

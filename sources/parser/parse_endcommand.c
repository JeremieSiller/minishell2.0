/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_endcommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:51:26 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/26 00:55:22 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int	parse_or(char **str, char **strbuf, t_cmds *cur)
{

}

static int	parse_and(char **str, char **strbuf, t_cmds *cur)	
{

}

static int	parse_pipe(char **str, char **strbuf, t_cmds *cur)
{

}

int	parse_endcommands(char **str,char **strbuf, t_cmds *cur)
{
	if (*str == '|' && *(str + 1) != '|')
		return (parse_pipe(str, strbuf, cur));
	if (*str == '|')
		return (parse_or(str, strbuf, cur));
	if (*str == '&')
		return (parse_and(str, strbuf, cur));
	else
		return (parse_space(str, strbuf, cur));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:51:35 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/26 03:40:47 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>

// WHAT HAPPENS WITH INPUT BEFORE REDIRECT SHIT 
// ASK JEREMY TOMORROW

static int	parse_heredoc(char **str, char **strbuf, t_cmds **cur)
{
	(void)strbuf;
	(*str) += 2;
	while (**str == ' ')
		(*str)++;
	while (!ft_strchr(HEREDOCEND, **str))
	{
		if (**str == '\'' || **str == '\"')
		{
			(*str)++;
			continue ;
		}
		if (char_append(&(*cur)->in_dir->path, **str))
			return (1);
		(*str)++;
	}
	if (append_list(cur))
		return (1);
	return (0);
}

static int	parse_leftfile(char **str, char **strbuf, t_cmds **cur)
{
	(void)str;
	(void)strbuf;
	(void)cur;
	return (0);
}

static int	parse_rightheredoc(char **str, char **strbuf, t_cmds **cur)
{
	(void)str;
	(void)strbuf;
	(void)cur;
	return (0);
	
}

static int	parse_rightfile(char **str, char **strbuf, t_cmds **cur)
{
	(void)str;
	(void)strbuf;
	(void)cur;
	return (0);
	
}

int parse_redirections(char **str, char **strbuf, t_cmds **cur, int *fc)
{
	*fc = 1;

	if (*strbuf)
		free(*strbuf);
	*strbuf = NULL;

	if (**str == '<')
	{
		(*cur)->in_dir = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
		if (!(*cur)->in_dir)
			return (1);
		if (*((*str) + 1) == '<')
			return (parse_heredoc(str, strbuf, cur));
		else
			return (parse_leftfile(str, strbuf, cur));
	}
	else
	{
		(*cur)->out_dir = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
		if (!(*cur)->out_dir)
			return (1);
		if (*((*str) + 1) == '>')
			return (parse_rightheredoc(str, strbuf, cur));
		else
			return (parse_rightfile(str, strbuf, cur));	
	}

	return (0);
}
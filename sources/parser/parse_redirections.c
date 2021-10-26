/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:51:35 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/26 03:08:48 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int	parse_heredoc(char **str, char **strbuf, t_cmds *cur)
{
	
}

static int	parse_leftfile(char **str, char **strbuf, t_cmds *cur)
{
	
}

static int	parse_rightheredoc(char **str, char **strbuf, t_cmds *cur)
{
	
}

static int	parse_rightfile(char **str, char **strbuf, t_cmds *cur)
{
	
}

int parse_redirections(char **str, char **strbuf, t_cmds *cur, int *fc)
{
	*fc = 1;

	if (**str == '<')
	{
		cur->in_dir = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
		if (!cur->in_dir)
			return (1);
		if (*((*str) + 1) == '<')
			return (parse_heredoc(str, strbuf, cur));
		else
			return (parse_leftfile(str, strbuf, cur));
	}
	else
	{
		cur->out_dir = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
		if (!cur->out_dir)
			return (1);
		if (*((*str) + 1) == '>')
			return (parse_rightheredoc(str, strbuf, cur));
		else
			return (parse_rightfile(str, strbuf, cur));	
	}

	return (0);
}
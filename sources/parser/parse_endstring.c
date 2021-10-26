/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_endstring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:51:31 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/26 18:19:48 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>

static int	parse_variable(char **str, char **strbuf)
{
	char	*var_name;

	var_name = NULL;
	(*str)++;
	while (!ft_strchr(REDIRECTIONS, **str) && !ft_strchr(ENDSTRING, **str)
		&& !ft_strchr(ENDCOMMAND, **str))
	{
		if (char_append(&var_name, **str))
			return (1);
		(*str)++;
	}
	--(*str);
	if (var_name)
	{
		//GET ACTUAL VALUE OF ENV VAR
		if (string_append(strbuf, var_name))
			return (1);
		free(var_name);
	}
	else if (char_append(strbuf, **str))
		return (1);
	return (0);
}

static int	parse_double(char **str, char **strbuf)
{
	(*str)++;
	while (**str != '\"')
	{
		if (**str == '\0')
			return (1);
		else if (**str != '$' && char_append(strbuf, **str))
			return (1);
		else if (**str == '$' && parse_variable(str, strbuf))
			return (1);
		(*str)++;
	}
	return (0);
}

static int	parse_single(char **str, char **strbuf)
{
	(*str)++;
	while (**str != '\'')
	{
		if (**str == '\0')
			return (1);
		else if (char_append(strbuf, **str))
			return (1);
		(*str)++;
	}
	return (0);
}

int	parse_qoutes(char **str, char **strbuf, int *fc)
{
	*fc = 1;
	if (**str == '\'')
		return (parse_single(str, strbuf));
	else if (**str == '\"')
		return (parse_double(str, strbuf));
	else
		return (parse_variable(str, strbuf));
}

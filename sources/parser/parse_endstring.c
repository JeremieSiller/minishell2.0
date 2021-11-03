/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_endstring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:51:31 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/03 18:01:51 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>


// IS NOT CORRECTLY PARSED STILL NEED TO FIGURE SHIT OUT
static int	parse_variable(char **str, char **strbuf)
{
	char	*var_name;
	char	*variable;

	var_name = NULL;
	(*str)++;
	if (ft_strchr("\'\"", **str) && (*str)--)
		return (0);
	while ((**str == '_' || ft_isalnum(**str)) && **str)
	{
		if (char_append(&var_name, **str))
			return (1);
		(*str)++;
	}
	--(*str);
	if (!var_name && *(*str + 1) == '?')
	{
		(*str)++;
		variable = ft_itoa(g_ourenv.exit_status);
		if (!variable)
			return (1);
		if (string_append(strbuf, variable))
			return (1);	
	}
	else if (var_name)
	{
		variable = ft_strdup(get_env_value(var_name));
		free(var_name);
		if (!variable)
			return (1);
		if (string_append(strbuf, variable))
			return (1);
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

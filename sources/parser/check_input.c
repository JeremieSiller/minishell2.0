/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:40:52 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/03 21:42:23by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <utilities.h>

int	set_incorrect(char **str, char **ret)
{
	(*str)++;
	while (ft_isspace(**str))
		(*str)++;
	if (ft_strchr(ENDCOMMAND, **str))
	{
		char_append(ret, **str);
		if (ft_strchr(ENDCOMMAND, *(*str + 1)))
			char_append(ret, **str);
	}
	else if (**str == '\"')
	{
		char_append(ret, **str);
		while (*(++(*str)) && **str != '\"')
			char_append(ret, **str);
		char_append(ret, **str);
	}
	else if (**str == '\'')
	{
		char_append(ret, **str);
		while (*(++(*str)) && **str != '\'')
			char_append(ret, **str);
		char_append(ret, **str);
	}
	else
	{
		while (**str && !ft_strchr(ENDCOMMAND, **str) && !(ft_strchr(ENDSTRING, **str) && **str != '$') && **str != ')' && !ft_isspace(**str))
		{
			char_append(ret, **str);
			(*str)++;
		}
	}
	(*str)--;
	return (1);
}

int	check_brack(char **str, char **ret)
{
	int	scope;

	(*str)++;
	*ret = check_input(*str);
	if (*ret)
		return (1);
	scope = 1;
	while (scope != 0 && **str)
	{
		if (**str == ')')
			scope--;
		else if (**str == '(')
			scope++;
		(*str)++;
	}
	(*str)--;
	if (scope != 0)
		if (char_append(ret, '('))
			return (1);
	if (*ret)
		return (1);
	return (0);
}

int	check_qoute(char **str, char **ret)
{
	(*str)++;
	if (*(*str - 1) == '\'')
	{
		while (**str && **str != '\'')
			(*str)++;
		if (!**str)
			char_append(ret, '\'');
	}
	else if (*(*str - 1) == '\"')
	{
		while (**str && **str != '\"')
			(*str)++;
		if (!**str)
			char_append(ret, '\"');
	}
	if (*ret)
		return (1);
	return (0);
}


/// REDIRECTIONS ARE MISSING WILL DO 
// CHECK IF EVERYTHING IS WORKING
char	*check_input(char *str)
{
	char	*ret;
	int		cmd;

	ret = NULL;
	cmd = 2;
	if (!str)
		return (ret);
	while (*str)
	{
		if ((*str == '(' && cmd != 2 && set_incorrect(&str, &ret))
			|| (*str == '(' && check_brack(&str, &ret)) || *str == ')')
			return (ret);
		else if (ft_strchr(ENDCOMMAND, *str))
		{
			if (cmd == 2)
			{
				char_append(&ret, *str);
				if (ft_strchr(ENDCOMMAND, *(str + 1)) && *str != '(')
					char_append(&ret, *(str + 1));
				return (ret);
			}
			if (ft_strchr(ENDCOMMAND, *(str + 1)) && *str != '(')
				str++;
			cmd = 2;
		}
		else if (ft_strchr(ENDSTRING, *str) && *str != '$' && check_qoute(&str, &ret))
			return (ret);
		else if (!ft_isspace(*str))
			cmd = 1;
		str++;
	}
	return (ret);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:36:18 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/05 14:49:49 by nschumac         ###   ########.fr       */
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
		while (**str && !ft_strchr(ENDCOMMAND, **str)
			&& !(ft_strchr(ENDSTRING, **str) && **str != '$')
			&& **str != ')' && !ft_isspace(**str))
		{
			char_append(ret, **str);
			(*str)++;
		}
	}
	(*str)--;
	return (1);
}

int	check_brack(char **str, char **ret, int scop2)
{
	int	scope;
	int	chars;

	(*str)++;
	*ret = check_input(*str, scop2 + 1);
	if (*ret && !ft_strncmp(*ret, ")", 2))
	{
		free(*ret);
		*ret = NULL;
	}
	if (*ret)
		return (1);
	scope = 1;
	chars = 0;
	while (scope != 0 && **str)
	{
		if (**str == ')')
			scope--;
		else if (**str == '(')
			scope++;
		(*str)++;
		chars++;
	}
	if (chars == 1)
		if (char_append(ret, ')'))
			return (1);
	if (scope != 0)
		if (char_append(ret, '('))
			return (1);
	if (*ret)
		return (1);
	(*str)--;
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

int	check_redirections(char **str, char **ret)
{
	if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
			(*str)++;
	}
	else
	{
		(*str)++;
		if (**str == '<')
			(*str)++;
	}	
	while (ft_isspace(**str))
		(*str)++;
	if (!**str)
	{
		*ret = ft_strdup("newline");
		return (1);
	}
	if (ft_strchr(ENDCOMMAND, **str))
	{
		char_append(ret, **str);
		if ((**str == '&' || **str == '|') && *(*str + 1) == **str)
			char_append(ret, **str);
		return (1);
	}
	else if (ft_strchr(REDIRECTIONS, **str))
	{
		char_append(ret, **str);
		return (1);
	}
	return (0);
}

// CHECK IF EVERYTHING IS WORKING
char	*check_input(char *str, int scope)
{
	char	*ret;
	int		cmd;
	int		bruh;

	ret = NULL;
	cmd = 2;
	if (!str)
		return (ret);
	while (*str)
	{
		bruh = 0;
		if ((*str == '(' && cmd != 2
				&& ++bruh == 1 && set_incorrect(&str, &ret))
			|| (*str == '(' && ++bruh == 1 && check_brack(&str, &ret, scope))
			|| (*str == ')' && scope != 0 && ++bruh == 1))
			return (ret);
		if (*str == ')' && ++bruh == 1)
		{
			char_append(&ret, ')');
			return (ret);
		}
		if (*str && ft_strchr(ENDCOMMAND, *str) && ++bruh == 1)
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
		else if (*str && ft_strchr(ENDSTRING, *str)
			&& *str != '$' && ++bruh == 1 && check_qoute(&str, &ret))
			return (ret);
		else if (*str && ft_strchr(REDIRECTIONS, *str)
			&& ++bruh == 1 && check_redirections(&str, &ret))
			return (ret);
		else if (!ft_isspace(*str))
			cmd = 1;
		if (str)
			str++;
	}
	return (ret);
}

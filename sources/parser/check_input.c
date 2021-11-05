/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:36:18 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/05 15:48:51 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <utilities.h>

static int	check_brack_2(char **str, char **ret, int *scope, int *chars)
{
	*scope = 1;
	*chars = 0;
	while (*scope != 0 && **str && !*ret)
	{
		if (**str == ')')
			(*scope)--;
		else if (**str == '(')
			(*scope)++;
		(*str)++;
		(*chars)++;
	}
	if ((*chars) == 1 && !*ret)
		if (char_append(ret, ')'))
			return (1);
	if ((*scope) != 0 && !*ret)
		if (char_append(ret, '('))
			return (1);
	return (0);
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
	if (check_brack_2(str, ret, &scope, &chars))
		return (1);
	if (*ret)
		return (1);
	(*str)--;
	return (0);
}

char	*check_input_2(char **str, char **ret, int *cmd, int *bruh)
{
	if (**str && ft_strchr(ENDCOMMAND, **str) && ++(*bruh) == 1)
	{
		if (*cmd == 2)
		{
			char_append(ret, **str);
			if (ft_strchr(ENDCOMMAND, *(*str + 1)) && **str != '(')
				char_append(ret, *(*str + 1));
			return (*ret);
		}
		if (ft_strchr(ENDCOMMAND, *(*str + 1)) && **str != '(')
			(*str)++;
		*cmd = 2;
	}
	else if (**str && ft_strchr(ENDSTRING, **str)
		&& **str != '$' && ++(*bruh) == 1 && check_qoute(str, ret))
		return (*ret);
	else if (**str && ft_strchr(REDIRECTIONS, **str)
		&& ++(*bruh) == 1 && check_redirections(str, ret))
		return (*ret);
	else if (!ft_isspace(**str))
		*cmd = 1;
	return (NULL);
}

// CHECK IF EVERYTHING IS WORKING
char	*check_input(char *str, int scope)
{
	char	*ret;
	int		cmd;
	int		bruh;

	ret = NULL;
	cmd = 2;
	while (str && *str)
	{
		bruh = 0;
		if ((*str == '(' && cmd != 2
				&& ++bruh == 1 && set_incorrect(&str, &ret))
			|| (*str == '(' && ++bruh == 1 && check_brack(&str, &ret, scope))
			|| (*str == ')' && scope != 0 && ++bruh == 1))
			return (ret);
		if (*str == ')' && ++(bruh) == 1)
		{
			char_append(&ret, ')');
			return (ret);
		}
		if (check_input_2(&str, &ret, &cmd, &bruh))
			return (ret);
		if (str)
			str++;
	}
	return (ret);
}

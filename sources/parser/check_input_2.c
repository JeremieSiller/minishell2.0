/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:26:38 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/05 15:35:49 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>

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
	(*str)++;
	if (**str == *(*str - 1))
		(*str)++;
	while (ft_isspace(**str))
		(*str)++;
	if (!**str)
	{
		*ret = ft_strdup("newline");
		return (1);
	}
	if (ft_strchr(ENDCOMMAND, **str) || ft_strchr(REDIRECTIONS, **str))
	{
		char_append(ret, **str);
		if ((**str == '&' || **str == '|') && *(*str + 1) == **str)
			char_append(ret, **str);
		return (1);
	}
	return (0);
}

static void	set_incorrect_2(char **str, char **ret)
{
	while (**str && !ft_strchr(ENDCOMMAND, **str)
		&& !(ft_strchr(ENDSTRING, **str) && **str != '$')
		&& **str != ')' && !ft_isspace(**str))
	{
		char_append(ret, **str);
		(*str)++;
	}
}

int	set_incorrect(char **str, char **ret)
{
	char	qt;

	(*str)++;
	while (ft_isspace(**str))
		(*str)++;
	if (ft_strchr(ENDCOMMAND, **str))
	{
		char_append(ret, **str);
		if (ft_strchr(ENDCOMMAND, *(*str + 1)))
			char_append(ret, **str);
	}
	else if (**str == '\"' || **str == '\'')
	{
		qt = **str;
		char_append(ret, **str);
		while (*(++(*str)) && **str != qt)
			char_append(ret, **str);
		char_append(ret, **str);
	}
	else
		set_incorrect_2(str, ret);
	(*str)--;
	return (1);
}

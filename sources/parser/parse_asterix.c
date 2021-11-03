/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asterix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:30:07 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/03 21:38:07 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <minishell.h>
#include <utilities.h>

static int	includepath(char *path, char *key)
{
	char	*pos;
	int		first;
	char	*before;
	char	*path1;

	first = 1;
	pos = ft_strchr(key, '*');
	if (ft_strlen(key) == 1)
		return (1);
	while (pos)
	{
		if (pos != key && first)
		{
			first = 0;
			if (ft_strncmp(path, key, pos - key))
				return (0);
			path += pos - key;
		}
		first = 0;
		before = pos;
		pos = ft_strchr(pos + 1, '*');
		if (!pos)
		{
			if (key[ft_strlen(key) - 1] == '*')
				return (1);
			if (ft_strnstr(path, before + 1, ft_strlen(path))
				== path + ft_strlen(path) - ft_strlen(before + 1))
				return (1);
			return (0);
		}
		*pos = '\0';
		path1 = ft_strnstr(path, before + 1, ft_strlen(path));
		*pos = '*';
		if (!path1)
			return (0);
		*pos = '\0';
		path = path1 + ft_strlen(before + 1);
		*pos = '*';
	}
	return (1);
}

int	parse_arsterix(char **str, char **strbuf, t_cmds **cur)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				amount;

	while (**str && !ft_strchr(ENDCOMMAND, **str) && **str != ' ')
	{
		if (!ft_strchr(ENDSTRING, **str) && char_append(strbuf, **str))
			return (1);
		(*str)++;
	}	
	dir = opendir("./");
	if (!dir)
		perror("minishell");
	if (!dir)
		return (1);
	dirent = readdir(dir);
	amount = 0;
	while (dirent)
	{
		if (ft_strncmp(dirent->d_name, ".", 1)
			&& includepath(dirent->d_name, *strbuf))
			if (++amount && dstring_append(&(*cur)->cmd,
					ft_strdup(dirent->d_name)))
				return (1);
		dirent = readdir(dir);
	}
	closedir(dir);
	if (amount > 0)
	{
		free(*strbuf);
		*strbuf = NULL;
	}
	(*str)--;
	return (0);
}

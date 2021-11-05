/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asterix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:30:07 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/05 15:24:58 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <minishell.h>
#include <utilities.h>

static int	includepath(char *path, char *key)
{
	char	*star;
	char	*old;
	char	*curpath;

	curpath = path;
	star = ft_strchr(key, '*');
	if (ft_strncmp(curpath, key, star - key))
		return (0);
	curpath += star - key;
	star = ft_strchr(key, '*');
	old = star + 1;
	star = ft_strchr(old, '*');
	while (star)
	{
		curpath = ft_strnstr(curpath, old, star - old);
		if (!curpath)
			return (0);
		old = star + 1;
		star = ft_strchr(old, '*');
	}
	star = ft_strrchr(key, '*') + 1;
	if (ft_strncmp((curpath + ft_strlen(curpath)
				- ft_strlen(star)), star, ft_strlen(curpath)))
		return (0);
	return (1);
}

static int	do_directory(char *key, t_cmds **cur, int *amount)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir("./");
	if (!dir)
		perror("minishell");
	if (!dir)
		return (1);
	dirent = readdir(dir);
	while (dirent)
	{
		if (ft_strncmp(dirent->d_name, ".", 1)
			&& includepath(dirent->d_name, key))
			if (++(*amount) && dstring_append(&(*cur)->cmd,
					ft_strdup(dirent->d_name)))
				return (1);
		dirent = readdir(dir);
	}
	closedir(dir);
	return (0);
}

int	parse_arsterix(char **str, char **strbuf, t_cmds **cur)
{
	int				amount;

	while (**str && !ft_strchr(ENDCOMMAND, **str) && **str != ' ')
	{
		if (ft_strchr(ENDSTRING, **str))
			parse_qoutes(str, strbuf);
		else if (char_append(strbuf, **str))
			return (1);
		(*str)++;
	}	
	if (do_directory(*strbuf, cur, &amount))
		return (1);
	if (amount > 0)
	{
		free(*strbuf);
		*strbuf = NULL;
	}
	(*str)--;
	return (0);
}

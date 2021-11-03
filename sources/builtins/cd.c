/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:20:46 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/03 16:03:02 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <utilities.h>
#include <builtins.h>

static int	update_pwd(char *str, char *arr[3])
{
	char	pwd[4096];

	if (get_env_value("PWD"))
	{
		if (!getcwd(pwd, 4096))
		{
			perror("minishell: cd");
			return (1);
		}
		str = ft_strjoin("PWD=", pwd);
		if (!str)
		{
			perror("minishell: cd");
			return (1);
		}
		arr[1] = str;
		if (bt_export(arr) == 1)
		{
			free(str);
			return (1);
		}
		free(str);
	}
	return (0);
}

static int	update_old_pwd(void)
{
	char	*str;
	char	*arr[3];

	arr[0] = "export";
	arr[2] = 0;
	if (get_env_value("OLDPWD"))
	{
		if (get_env_value("PWD"))
			str = ft_strjoin("OLDPWD=", get_env_value("PWD"));
		else
			str = ft_strdup("OLDPWD=");
		if (!str)
		{
			perror("minishell: cd");
			return (1);
		}
		arr[1] = str;
		if (bt_export(arr) == 1)
		{
			free(str);
			return (1);
		}
		free(str);
	}
	return (update_pwd(0, arr));
}

int	bt_cd(char **argv)
{
	argv++;
	if (!*argv)
	{
		if (!get_env_value("HOME"))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		if (chdir(get_env_value("HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(get_env_value("HOME"));
			return (1);
		}
	}
	else if (chdir(*argv) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(*argv);
		return (1);
	}
	return (update_old_pwd());
}

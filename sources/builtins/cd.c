/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:20:46 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/28 16:54:31 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// handle home
// handle env -> set PWD ->set OLDPWD
int	bt_cd(char **argv)
{
	argv++;
	if (!*argv)
	{
		// handle home
		// handle if home not set
		return (0);
	}
	if (chdir(*argv) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(*argv);
		return (1);
	}
	return (0);
}

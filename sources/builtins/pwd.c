/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:26:42 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/28 16:47:58 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bt_pwd(char **argv)
{
	char	str[4096];

	if (!getcwd(str, 4096))
	{
		perror("minishell");
		return (1);
	}
	printf("%s\n", str);
	return (0);
	(void)argv;
}

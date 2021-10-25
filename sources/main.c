/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:12 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/25 22:36:12 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>



int	main(int argc, char *argv[], char **env)
{

	char *str = readline(">");

	// t_cmds *list = parse(str);



	// while (list)
	// {
		
	// 	list = list->next;
	// }

	return (0);
	(void)argc;
	(void)argv;
	(void)env;
	(void)str;
}
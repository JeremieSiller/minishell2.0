/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:08 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/25 22:36:08 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	double_qoutes(char *str, int *cnt)
{

}

int	single_qoutes(char *str, int *cnt)
{

}

t_cmds	*parse(char *str)
{	
	int		cnt;
	t_cmds	*head;

	cnt = 0;	
	while (str[cnt])
	{
		if (str[cnt] == '\"' && !double_qoutes(str, &cnt))
			return (NULL);
		


		cnt++;
	}


	return (head);
}



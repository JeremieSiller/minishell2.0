/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:38:44 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/25 22:38:45 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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



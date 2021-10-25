/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:38:44 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/25 23:55:17 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <utilities.h>

int	parse_double(char *str, int *cnt, char **strbuf, t_cmds *cur)
{

}

int	parse_single(char *str, int *cnt, char **strbuf, t_cmds *cur)
{

}

int	parse_variable(char *str, int *cnt, char **strbuf, t_cmds *cur)
{

}

int	parse_pipe(char *str, int *cnt, char **strbuf, t_cmds *cur)
{
	
}

int	parse_space(char *str, int *cnt, char **strbuf, t_cmds *cur)
{
	
}

int parse_redirections(char *str, int *cnt, char **strbuf, t_cmds *cur)
{

}

t_cmds	*parse(char *str)
{	
	int		cnt;
	char	*strbuf;
	t_cmds	*cur;

	cnt = 0;
	while (str[cnt])
	{
		if (str[cnt] == '\"' && parse_double(str, &cnt, &strbuf, cur))
			return (clear_list(cur, NULL));
		else if (str[cnt] == '\'' && parse_single(str, &cnt, &strbuf, cur))
			return (clear_list(cur, NULL));
		else if (str[cnt] == '$' && parse_variable(str, &cnt, &strbuf, cur))
			return (clear_list(cur, NULL));
		else if (str[cnt] == '|' &&	parse_pipe(str, &cnt, &strbuf, cur))	
			return (clear_list(cur, NULL));
		else if (str[cnt] == ' ' && parse_space(str, &cnt, &strbuf, cur))
			return (clear_list(cur, NULL));
		else if (ft_strchr(REDIRECTIONS, str[cnt]) && parse_redirections(str, &cnt, &strbuf, cur))
			return (clear_list(cur, NULL));
		else if (char_append(&strbuf, str[cnt]))
			return (clear_list(cur, NULL));
		cnt++;
	}
	if (strbuf)
		if(string_append(&cur->cmd, strbuf))
			return (clear_list(cur, NULL));
	return (find_listhead(cur));
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:02 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/26 02:28:21 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell.h> 

# define REDIRECTIONS "<>"
# define ENDSTRING "\"\'$"
# define ENDCOMMAND "&|"

t_cmds	*parse(char *str);

int	parse_qoutes(char **str, char **strbuf, int *fc);

int	parse_redirections(char **str, char **strbuf, t_cmds *cur, int *fc);

int	parse_endcommands(char **str,char **strbuf, t_cmds **cur, int *fc);

#endif
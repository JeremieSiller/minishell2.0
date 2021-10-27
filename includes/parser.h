/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:02 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/27 20:19:29 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell.h> 

# define REDIRECTIONS "<>"
# define ENDSTRING "\"\'$"
# define ENDCOMMAND "&|("
# define HEREDOCEND " |&"
# define VARIABLE_CHARS "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

t_cmds	*parse(char *str, t_cmds *cur, char *argv);

int		check_input(char *str);

int		parse_qoutes(char **str, char **strbuf, int *fc);

int		parse_redirections(char **str, char **strbuf, t_cmds **cur, int *fc);

int		parse_endcommands(char **str,char **strbuf, t_cmds **cur, int *fc, char *argv);

#endif
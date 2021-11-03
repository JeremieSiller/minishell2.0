/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:02 by jsiller           #+#    #+#             */
/*   Updated: 2021/11/03 19:35:18 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell.h> 

# define REDIRECTIONS "<>"
# define ENDSTRING "\"\'$"
# define ENDCOMMAND "&|("
# define HEREDOCEND " |&"

t_cmds	*parse(char *str, t_cmds *cur, char *argv);

int		check_input(char *str);

int		parse_qoutes(char **str, char **strbuf);

int		parse_endcommands(char **str, char **strbuf, t_cmds **cur, char *argv);

int		add_redirect(t_redirect ***cur);

int		redirect_size(t_redirect **red);

int		parse_redirections(char **str, char **strbuf, t_cmds **cur);

int		parse_redirections_2(char **str, t_cmds **cur);

int		parse_arsterix(char **str, char **strbuf, t_cmds **cur);
#endif
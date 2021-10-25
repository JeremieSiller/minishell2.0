/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:36:02 by jsiller           #+#    #+#             */
/*   Updated: 2021/10/25 23:27:32 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell.h> 

# define REDIRECTIONS "<>"
t_cmds	*parse(char *str);


#endif
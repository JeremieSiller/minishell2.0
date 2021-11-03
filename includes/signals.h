/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:09:40 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/02 15:12:14 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <minishell.h>

void	gsignal_ctlc(int sigtype);
void	fsignal_ctlc(int sigtype);
int		changetermios(bool toggle);
int		our_minishell(char *cmd);
#endif
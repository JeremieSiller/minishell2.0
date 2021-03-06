/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsiller <jsiller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:09:40 by nschumac          #+#    #+#             */
/*   Updated: 2021/11/04 17:52:58 by jsiller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <minishell.h>

void	gsignal_ctlc(int sigtype);
void	fsignal_ctlc(int sigtype);
void	heredoc_ctlc(int sigtype);
int		changetermios(bool toggle);
#endif
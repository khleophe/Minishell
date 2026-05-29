/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:47:26 by nolwenng          #+#    #+#             */
/*   Updated: 2026/05/29 15:18:32 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); // voir man de ces fonctions
}

void	init_sign(struct sigaction *sig_int, struct sigaction *sig_quit)
{
	sigemptyset(&sig_int->sa_mask);
	sig_int->sa_handler = handle_sigint;
	sig_int->sa_flags = SA_RESTART; // a voir les flags
	sigemptyset(&sig_quit->sa_mask);
	sig_quit->sa_handler = SIG_IGN;
	sig_quit->sa_flags = SA_RESTART;
}


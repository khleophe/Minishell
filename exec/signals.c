/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:47:26 by nolwenng          #+#    #+#             */
/*   Updated: 2026/07/03 16:27:23 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void) sig;
	if (flag != 1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay(); // voir man de ces fonctions
	}
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

void	child_int(int signum)
{
	(void)signum;
	exit(130);
}

void	init_sign_heredoc(struct sigaction *sig_child_int, struct sigaction *sig_child_quit)
{
	sigemptyset(&sig_child_int->sa_mask);
	sig_child_int->sa_handler = child_int;
	sig_child_int->sa_flags = SA_RESTART; // a voir les flags
	sigemptyset(&sig_child_quit->sa_mask);
	sig_child_quit->sa_handler = SIG_IGN;
	sig_child_quit->sa_flags = SA_RESTART;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 15:11:56 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/06 23:04:58 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	if (g_flag != 1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_sign(struct sigaction *sig_int, struct sigaction *sig_quit)
{
	sigemptyset(&sig_int->sa_mask);
	sig_int->sa_handler = handle_sigint;
	sig_int->sa_flags = SA_RESTART;
	sigemptyset(&sig_quit->sa_mask);
	sig_quit->sa_handler = SIG_IGN;
	sig_quit->sa_flags = SA_RESTART;
}

void	child_int(int signum)
{
	g_flag = signum;
	close(STDIN_FILENO);
	get_data()->stdin_open = 0;
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n", 1);
	get_data()->return_code = 130;
}

void	init_sign_heredoc(struct sigaction *sig_child_int,
		struct sigaction *sig_child_quit)
{
	sigemptyset(&sig_child_int->sa_mask);
	sig_child_int->sa_handler = child_int;
	sig_child_int->sa_flags = SA_RESTART;
	sigemptyset(&sig_child_quit->sa_mask);
	sig_child_quit->sa_handler = SIG_IGN;
	sig_child_quit->sa_flags = SA_RESTART;
}

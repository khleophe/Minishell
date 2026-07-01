/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:47:26 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/20 15:44:33 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*2. g_signal — jamais lu
Tu le set à 130 dans le handler SIGINT mais tu ne l'utilises nulle part. 
Il sert normalement à transmettre le code de retour 130 au main après un Ctrl+C.
C'est un morceau manquant.
*/
// int	g_signal;

static void	handle_sigint(int sig)
{
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	interactive_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	exec_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}


//icic c;est chew jojo
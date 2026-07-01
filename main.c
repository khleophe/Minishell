/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:45:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/05/29 15:16:29 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;	
	data.tokens = NULL;
	data.env = dup_env(envp);
    data.return_code = 0;
	init_sign(&data.sig_int, &data.sig_quit);
    sigaction(SIGINT, &data.sig_int, NULL);
	sigaction(SIGQUIT, &data.sig_quit, NULL);
	if (!data.env)
		return (1);
	read_line(&data.tokens, &data);
	free_tokens(data.tokens);
	// rl_clear_history
	// free
	return (0);
}

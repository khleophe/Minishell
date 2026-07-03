/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:45:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/03 17:08:35 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	flag = 0;
	data.old_stdin = dup(STDIN_FILENO);
	data.old_stdout = dup(STDOUT_FILENO);
	data.tokens = NULL;
	data.env = dup_env(envp);
    data.return_code = 0;
	init_sign(&data.sig_int, &data.sig_quit);
	init_sign_heredoc(&data.sig_child_int, &data.sig_child_quit);
    sigaction(SIGINT, &data.sig_int, NULL);
	sigaction(SIGQUIT, &data.sig_quit, NULL);
	if (!data.env)
		return (1);
	read_line(&data.tokens, &data);
	free_tokens(data.tokens);
	close(data.old_stdin);
	close(data.old_stdout);
	// rl_clear_history
	// free
	return (0);
}

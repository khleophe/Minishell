/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:45:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/23 17:48:54 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_flag = 0;

static void	read_cli(t_token **tokens, t_data *data, char *line)
{
	data->pipe_nb = 0;
	if (line == NULL)
		clean(NULL, data, 0);
	g_flag = 1;
	add_history(line);
	*tokens = lexer(line);
	if (check_syntax(data))
	{
		free_tokens(*tokens);
		*tokens = NULL;
	}
	else
	{
		expand_all_tokens(*tokens, data);
		if (tokens)
			exec_pipe(data);
		if (dup2(data->old_stdin, STDIN_FILENO) == -1)
			clean("error: dup2", data, 1);
		if (dup2(data->old_stdout, STDOUT_FILENO) == -1)
			clean("error: dup2", data, 1);
		free_tokens(*tokens);
		*tokens = NULL;
	}
	g_flag = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = get_data();
	(void)argc;
	(void)argv;
	g_flag = 0;
	init(data, envp);
	if (argc == 2)
		read_cli(&data->tokens, data, argv[1]);
	else
		read_line(&data->tokens, data);
	clean(NULL, data, 0);
	return (0);
}

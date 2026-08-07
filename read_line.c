/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:26:31 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/07 03:31:01 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verif_line(char *str)
{
	if (!str[0] || str[0] == '\n')
		return (0);
	return (1);
}

static void	read_line_next(t_token **tokens, t_data *data)
{
	expand_all_tokens(*tokens, data);
	if (tokens)
		exec_pipe(data);
	wait_all(data);
	if (data->current_stdin > 0)
		close(data->current_stdin);
	data->current_stdin = -1;
	if (dup2(data->old_stdin, STDIN_FILENO) < 0)
		clean("error", data, 1);
	if (dup2(data->old_stdout, STDOUT_FILENO) < 0)
		clean("error", data, 1);
	data->stdin_open = 1;
	free_tokens(*tokens);
	*tokens = NULL;
	data->one_built = 0;
}

static void	print_error(t_token **tokens, t_data *data)
{
	ft_printf("syntax error\n");
	data->return_code = 2;
	free_tokens(*tokens);
	*tokens = NULL;
}

void	read_line(t_token **tokens, t_data *data)
{
	char	*line;

	while (1)
	{
		data->pipe_nb = 0;
		line = readline("minishell>");
		if (line == NULL)
			clean(NULL, data, 0);
		if (verif_line(line))
		{
			g_flag = 1;
			add_history(line);
			*tokens = lexer(line);
			free(line);
			if (check_syntax(data))
				print_error(tokens, data);
			else
				read_line_next(tokens, data);
		}
		g_flag = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:26:31 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/05 12:45:27 by jdelmott         ###   ########.fr       */
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
	if (data->old_stdin > 0)
		close(data->old_stdin);
	data->old_stdin = -1;
	free_tokens(*tokens);
	*tokens = NULL;
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

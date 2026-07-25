/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:27:13 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/25 20:38:05 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_pipe(t_data *data, int pipe_fd[2], int return_value, char *s)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	clean(s, data, return_value);
}

static int	create_child(t_data *data, t_token **token)
{
	int		return_code;

	return_code = 0;
	// if (pipe(pipe_fd) == -1)
	// 	clean("error: pipe", data, 1);
	return_code = parsing_cmd(data, *token);
	// child = fork();
	// if (!child)
	// {
	// 	if (dup2(pipe_fd[1], 1) < 0)
	// 		exit_pipe(data, pipe_fd, return_code, "dup2: error");
	// 	return_code = parsing_cmd(data, *token);
	// 	exit_pipe(data, pipe_fd, return_code, NULL);
	// }
	// else if (child != -1)
	// {
	// 	if (dup2(pipe_fd[0], 0) < 0)
	// 		exit_pipe(data, pipe_fd, return_code, "dup2: error");
		while ((*token) && (*token)->type != PIPE)
			(*token) = (*token)->next;
		if ((*token)->type == PIPE)
			(*token) = (*token)->next;
	// }
	return (return_code);
}

int	exec_pipe(t_data *data)
{
	t_token	*tmp;

	data->pipe_done = 0;
	tmp = data->tokens;
	while (data->pipe_done < data->pipe_nb)
	{
		data->return_code = create_child(data, &tmp);
		if (data->return_code != 0)
			return (data->return_code);
		data->pipe_done++;
	}
	data->return_code = parsing_cmd(data, tmp);
	return (data->return_code);
}

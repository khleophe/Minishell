/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:27:13 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/16 11:25:03 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_pipe(t_data *data, int pipe_fd[2], int return_value, char *s)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	clean(s, data, return_value);
}

static int	create_child(t_data *data, t_token **token)
{
	pid_t	child;
	int		pipe_fd[2];
	int		return_code;

	return_code = 0;
	if (pipe(pipe_fd) == -1)
		clean("error: pipe", data, 1);
	child = fork();
	if (!child)
	{
		if (dup2(pipe_fd[1], 1) < 0)
			exit_pipe(data, pipe_fd, return_code, "dup2: error");
		return_code = parsing_cmd(data, *token);
		exit_pipe(data, pipe_fd, return_code, NULL);
	}
	else
	{
		if (dup2(pipe_fd[0], 0) < 0)
			exit_pipe(data, pipe_fd, return_code, "dup2: error");
		while ((*token) && (*token)->type != PIPE)
			(*token) = (*token)->next;
		if ((*token)->type == PIPE)
			(*token) = (*token)->next;
	}
	return (close(pipe_fd[1]), close(pipe_fd[0]), 0);
}

int	exec_pipe(t_data *data)
{
	t_token	*tmp;
	int		pipe_done;

	pipe_done = 0;
	tmp = data->tokens;
	while (pipe_done < data->pipe_nb)
	{
		data->return_code = create_child(data, &tmp);
		if (data->return_code != 0)
			return (data->return_code);
		pipe_done++;
	}
	data->return_code = parsing_cmd(data, tmp);
	return (data->return_code);
}

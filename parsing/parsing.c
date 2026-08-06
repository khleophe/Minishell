/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:41:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/06 22:12:54 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	little_pipe(t_data *data, t_redirections *r)
{
	pid_t	child;
	int		fd[2];

	pipe(fd);
	child = fork();
	if (child == 0)
	{
		if (dup2(fd[1], 1) < 0)
			return (close(fd[0]), close(fd[1]), clean("error: dup2", data, 1),
				1);
		if (apply_redir(r) == 1)
			return (close(fd[0]), close(fd[1]), clean("error: dup2", data, 1),
				1);
		close(fd[0]);
		close(fd[1]);
		return (clean_redirs(r), clean(NULL, data, 0), 1);
	}
	else
	{
		if (data->current_stdin != 0)
			close(data->current_stdin);
		data->current_stdin = fd[0];
	}
	close(fd[1]);
	return (0);
}

int	parsing_cmd(t_data *data, t_token *tokens, int return_code)
{
	t_redirections	redirections;

	ft_memset(&redirections, 0, sizeof(redirections));
	redirections.infd = 0;
	redirections.outfd = 1;
	return_code = create_redirs(tokens, &redirections);
	if (return_code != 0)
		return (return_code);
	return_code = -1;
	while (tokens && tokens->type != PIPE)
	{
		while (tokens && is_redirs(tokens->type))
			tokens = tokens->next->next;
		if (tokens && tokens->type == WORD && tokens->type != PIPE)
		{
			return_code = parsing_builtin(data, &tokens, &redirections);
			if (tokens && tokens->type == WORD)
				return_code = exec(data, &tokens, &redirections);
			while (tokens && tokens->type == WORD)
				tokens = tokens->next;
		}
	}
	if (return_code == -1 && data->pipe_nb > 0
		&& data->pipe_done < data->pipe_nb)
		return_code = little_pipe(data, &redirections);
	return (clean_redirs(&redirections), return_code);
}

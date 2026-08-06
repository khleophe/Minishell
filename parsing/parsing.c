/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:41:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/06 17:31:59 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_bultin(t_data *data, t_token **token, int mode)
{
	if (mode == 0)
		return (parsing_env(data, token));
	if (mode == 1)
		return (parsing_unset(data, token));
	if (mode == 2)
		return (parsing_pwd(data, token));
	if (mode == 3)
		return (parsing_export(data, token));
	if (mode == 4)
		return (parsing_exit(data, token));
	if (mode == 5)
		return (parsing_echo(token));
	if (mode == 6)
		return (parsing_cd(data, token));
	return (1);
}

static void	child_builtin(t_data *data, t_token **token, int pipe_fd[2],
		t_redirections *r)
{
	if (data->current_stdin > 0)
	{
		if (dup2(data->current_stdin, 0) < 0)
			clean("error: dup2", get_data(), 1);
		close(data->current_stdin);
		data->current_stdin = 0;
	}
	if (data->pipe_nb > 0 && data->pipe_done < data->pipe_nb)
	{
		if (dup2(pipe_fd[1], 1) < 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			clean("error: dup2", data, 1);
		}
	}
	if (data->pipe_nb > 0 && data->pipe_done <= data->pipe_nb)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (apply_redir(r) == 1)
		clean("error: dup2", data, 1);
	data->return_code = apply_bultin(data, token, data->mode_builtin);
	clean(NULL, data, data->return_code);
}

static int	builtin_pipe(t_data *data, t_token **token, int mode,
		t_redirections *r)
{
	pid_t	child;
	int		pipe_fd[2];

	data->mode_builtin = mode;
	if (data->pipe_nb == 0)
		return (data->one_built = 1, apply_bultin(data, token, mode));
	pipe(pipe_fd);
	child = fork();
	if (child == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), clean("no", data, 1), 1);
	if (child == 0)
		child_builtin(data, token, pipe_fd, r);
	else
	{
		clean_redirs(r);
		if (data->pipe_nb > 0 && data->pipe_done <= data->pipe_nb)
			change_current_stdin(data, pipe_fd);
		while ((*token) && (*token)->type != PIPE)
			(*token) = (*token)->next;
		data->children[data->pipe_done] = child;
		return (0);
	}
	return (close(pipe_fd[1]), close(pipe_fd[0]), 0);
}

int	parsing_builtin(t_data *data, t_token **token, t_redirections *r)
{
	if (ft_strcmp((*token)->s, "env") == 0)
		return (builtin_pipe(data, token, 0, r));
	if (ft_strcmp((*token)->s, "unset") == 0)
		return (builtin_pipe(data, token, 1, r));
	if (ft_strcmp((*token)->s, "pwd") == 0)
		return (builtin_pipe(data, token, 2, r));
	if (ft_strcmp((*token)->s, "export") == 0)
		return (builtin_pipe(data, token, 3, r));
	if (ft_strcmp((*token)->s, "exit") == 0)
		return (builtin_pipe(data, token, 4, r));
	if (ft_strcmp((*token)->s, "echo") == 0)
		return (builtin_pipe(data, token, 5, r));
	if (ft_strcmp((*token)->s, "cd") == 0)
		return (builtin_pipe(data, token, 6, r));
	else
		return (0);
}

int	little_pipe(t_data *data, t_redirections *r)
{
	pid_t child;
	int	fd[2];

	pipe(fd);
	child = fork();
	if (child == 0)
	{
		if (dup2(fd[1], 1) < 0)
			return (close(fd[0]), close(fd[1]), clean("error: dup2", data, 1), 1);
		if (apply_redir(r) == 1)
			return (close(fd[0]), close(fd[1]), clean("error: dup2", data, 1), 1);
		close(fd[0]);
		close(fd[1]);
		clean(NULL, data, 0);
	}
	else
		data->current_stdin = fd[0];
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
	if (return_code == -1)
		return_code = little_pipe(data, &redirections);
	return (clean_redirs(&redirections), return_code);
}



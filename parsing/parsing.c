/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:41:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/24 17:53:18 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int apply_bultin(t_data *data, t_token **token, int mode)
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

static int builtin_pipe(t_data *data, t_token **token, int mode)
{
	pid_t	child;
	int		status;
	int		return_code;
	int		pipe_fd[2];
	
	if (data->pipe_nb > 0 && data->pipe_done <= data->pipe_nb)
	{
		pipe(pipe_fd);
		child = fork();
		if (child == 0)
		{
			if (data->pipe_nb > 0 && data->pipe_done < data->pipe_nb)
				dup2(pipe_fd[1], 1);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return_code = apply_bultin(data, token, mode);
			clean(NULL, data, return_code);
		}
		else
		{
			waitpid(child, &status, 0);
			dup2(pipe_fd[0], 0);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			while ((*token) && (*token)->type != PIPE)
				(*token) = (*token)->next;
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
	}
	return (apply_bultin(data, token, mode));
}

int	parsing_builtin(t_data *data, t_token **token)
{
	if (ft_strcmp((*token)->s, "env") == 0)
		return (builtin_pipe(data, token, 0));
	if (ft_strcmp((*token)->s, "unset") == 0)
		return (builtin_pipe(data, token, 1));
	if (ft_strcmp((*token)->s, "pwd") == 0)
		return (builtin_pipe(data, token, 2));
	if (ft_strcmp((*token)->s, "export") == 0)
		return (builtin_pipe(data, token, 3));
	if (ft_strcmp((*token)->s, "exit") == 0)
		return (builtin_pipe(data, token, 4));
	if (ft_strcmp((*token)->s, "echo") == 0)
		return (builtin_pipe(data, token, 5));
	if (ft_strcmp((*token)->s, "cd") == 0)
		return (builtin_pipe(data, token, 6));
	else
		return (0);
}

int	parsing_cmd(t_data *data, t_token *tokens)
{
	int	return_code;

	return_code = 0;
	if (apply_redirs(tokens, &return_code, data))
		return (return_code);
	while (tokens && tokens->type != PIPE)
	{
		while (tokens && is_redirs(tokens->type))
			tokens = tokens->next->next;
		if (tokens && tokens->type == WORD && tokens->type != PIPE)
		{
			return_code = parsing_builtin(data, &tokens);
			if (tokens && tokens->type == WORD)
				return_code = exec(data, &tokens);
			while (tokens && tokens->type == WORD)
				tokens = tokens->next;
		}
		else if (tokens && tokens->type != WORD && tokens->type != PIPE)
			tokens = tokens->next;
	}
	return (return_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:37:37 by nolwenng          #+#    #+#             */
/*   Updated: 2026/08/07 00:16:15 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_env(char **env)
{
	char	**dup;
	int		n;

	n = 0;
	while (env[n] != NULL)
		n++;
	dup = malloc(sizeof(char *) * (n + 1));
	if (!dup)
		return (NULL);
	n = 0;
	while (env[n] != NULL)
	{
		dup[n] = ft_strdup(env[n]);
		if (!dup[n])
		{
			while (n > 0)
				free(dup[--n]);
			free(dup);
			return (NULL);
		}
		n++;
	}
	dup[n] = NULL;
	return (dup);
}

t_data	*get_data(void)
{
	static t_data	*data = 0;

	if (!data)
	{
		data = malloc(sizeof(*data));
		if (!data)
			exit(1);
	}
	return (data);
}

void	init(t_data *data, char **env)
{
	data->current_stdin = 0;
	data->mode_builtin = -1;
	data->one_built = 0;
	data->stdin_open = 1;
	data->tokens = NULL;
	data->env = dup_env(env);
	data->old_stdin = dup(STDIN_FILENO);
	if (data->old_stdin == -1)
		clean("error: dup", data, 1);
	if (!data->env)
		clean("error: dup_env", data, 1);
	data->return_code = 0;
	init_sign(&data->sig_int, &data->sig_quit);
	init_sign_heredoc(&data->sig_child_int, &data->sig_child_quit);
	sigaction(SIGINT, &data->sig_int, NULL);
	sigaction(SIGQUIT, &data->sig_quit, NULL);
	if (get_pwd(data) == 1)
		clean("error: get_pwd", data, 1);
}

void	change_current_stdin(t_data *data, int pipe_fd[2])
{
	if (data->current_stdin > 0)
		close(data->current_stdin);
	data->current_stdin = pipe_fd[0];
	close(pipe_fd[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:37:37 by nolwenng          #+#    #+#             */
/*   Updated: 2026/08/05 16:02:45 by jdelmott         ###   ########.fr       */
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

void	init(t_data *data, char **env)
{
	data->current_stdin = 0;
	data->heredoc_fd[0] = -1;
	data->heredoc_fd[1] = -1;
	data->mode_builtin = -1;
	data->tokens = NULL;
	data->env = dup_env(env);
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

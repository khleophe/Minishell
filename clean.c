/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:57:58 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/07 00:15:07 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_files(t_data *data)
{
	if (data->current_stdin > 0)
		close(data->current_stdin);
	data->current_stdin = -1;
}

void	clean_redirs(t_redirections *r)
{
	if (r->in_mode != DEFAULT && r->infd != 0)
		close(r->infd);
	r->in_mode = DEFAULT;
	if (r->out_mode != DEFAULT && r->outfd != 1)
		close(r->outfd);
	r->out_mode = DEFAULT;
}

void	clean(char *str, t_data *data, int return_code)
{
	struct termios	termios;

	ft_memset(&termios, 0, sizeof(termios));
	tcgetattr(0, &termios);
	termios.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &termios);
	if (data->old_stdin != -1)
		close(data->old_stdin);
	clean_files(data);
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->env)
		ft_freetab(data->env);
	if (str)
		ft_putstr_fd(str, 2);
	if (data->stdin_open == 1)
		close(0);
	free(get_data());
	close(1);
	close(2);
	exit(return_code);
}

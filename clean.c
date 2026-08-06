/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:57:58 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/06 21:11:20 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_files(t_data *data)
{
	if (data->current_stdin > 0)
		close(data->current_stdin);
	data->current_stdin = -1;
	if (data->heredoc_fd[0] != -1)
		close(data->heredoc_fd[0]);
	if (data->heredoc_fd[1] != -1)
		close(data->heredoc_fd[1]);
}

void	clean_redirs(t_redirections *r)
{
	if (r->in_mode != DEFAULT)
		close(r->infd);
	r->in_mode = DEFAULT;
	if (r->out_mode != DEFAULT)
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
	clean_files(data);
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->env)
		ft_freetab(data->env);
	if (str)
		ft_putstr_fd(str, 2);
	free(get_data());
	close(0);
	close(1);
	close(2);
	exit(return_code);
}

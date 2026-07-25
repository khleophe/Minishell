/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:04:30 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/23 17:50:21 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(char *lim, int fd)
{
	char			*scan;
	struct termios	termios;

	tcgetattr(0, &termios);
	termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termios);
	scan = readline("heredoc> ");
	while (scan && ft_strcmp(scan, lim) != 0)
	{
		if (scan && ft_strcmp(scan, lim) != 0)
			ft_printf_fd(fd, "%s\n", scan);
		free(scan);
		scan = readline("heredoc> ");
	}
	free(scan);
}

int	heredoc_redir(char *eof, t_data *data)
{
	if (pipe(data->heredoc_fd) != 0)
		return (1);
	sigaction(SIGINT, &data->sig_child_int, 0);
	sigaction(SIGQUIT, &data->sig_child_quit, 0);
	read_heredoc(eof, data->heredoc_fd[1]);
	sigaction(SIGINT, &data->sig_int, NULL);
	sigaction(SIGQUIT, &data->sig_quit, NULL);
	close(data->heredoc_fd[1]);
	data->heredoc_fd[1] = -1;
	return (0);
}

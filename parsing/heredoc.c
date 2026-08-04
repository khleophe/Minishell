/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:04:30 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/04 16:37:12 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(char *lim, int fd, t_data *data)
{
	char			*scan;
	char			*quotes;
	struct termios	termios;

	tcgetattr(0, &termios);
	termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termios);
	scan = readline("heredoc> ");
	while (scan && ft_strcmp(scan, lim) != 0)
	{
		scan = expand_str_quotes(scan, data);
		quotes = remove_quotes(scan);
		if (scan && ft_strcmp(scan, lim) != 0)
			ft_printf_fd(fd, "%s\n", quotes);
		free(scan);
		free(quotes);
		scan = readline("heredoc> ");
	}
	free(scan);
}

int	heredoc_redir(char *eof, t_data *data)
{
	if (data->heredoc_fd[0] != -1)
	{
		close(data->heredoc_fd[0]);
		data->heredoc_fd[0] = -1;
	}
	if (data->heredoc_fd[1] != -1)
	{
		close(data->heredoc_fd[1]);
		data->heredoc_fd[1] = -1;
	}
	if (pipe(data->heredoc_fd) != 0)
		return (1);
	sigaction(SIGINT, &data->sig_child_int, 0);
	sigaction(SIGQUIT, &data->sig_child_quit, 0);
	read_heredoc(eof, data->heredoc_fd[1], data);
	sigaction(SIGINT, &data->sig_int, NULL);
	sigaction(SIGQUIT, &data->sig_quit, NULL);
	close(data->heredoc_fd[1]);
	data->heredoc_fd[1] = -1;
	return (0);
}

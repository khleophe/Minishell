/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:04:30 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/06 22:26:43 by jdelmott         ###   ########.fr       */
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

int	heredoc_redir(char *eof, t_data *data, int heredoc_fd[2])
{
	if (pipe(heredoc_fd) != 0)
		return (1);
	sigaction(SIGINT, &data->sig_child_int, 0);
	sigaction(SIGQUIT, &data->sig_child_quit, 0);
	read_heredoc(eof, heredoc_fd[1], data);
	sigaction(SIGINT, &data->sig_int, NULL);
	sigaction(SIGQUIT, &data->sig_quit, NULL);
	close(heredoc_fd[1]);
	heredoc_fd[1] = -1;
	return (0);
}

int	parsing_heredoc(t_redirections *r, char *eof)
{
	int	ret;
	int	heredoc_fd[2];

	ret = 0;
	ret = heredoc_redir(eof, get_data(), heredoc_fd);
	if (r->infd != 0)
		close(r->infd);
	r->infd = heredoc_fd[0];
	r->in_mode = IN_HEREDOC;
	return (ret);
}

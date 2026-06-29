/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:01:39 by nolwenng          #+#    #+#             */
/*   Updated: 2026/06/24 16:50:02 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sig_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

static void	write_expanded(char *line, int fd, t_data *data)
{
	char	*expanded;
	char	*dup;

	dup = ft_strdup(line);
	if (!dup)
		return ;
	expanded = expand_str(dup, data);
	if (expanded)
	{
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
}

void	mess_heredoc(t_redir *redirs, int count)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted \'", 2);
	ft_putstr_fd(redirs->file, 2);
	ft_putstr_fd("')\n", 2);
}

void	handle_redir_heredoc(t_redir *redirs, t_data *data)
{
	int		fd[2];
	char	*line;
	int		count;

	count = 1;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	signal(SIGINT, handle_sig_heredoc);
	line = readline("heredoc> ");
	while (line != NULL && (ft_strcmp(line, redirs->file) != 0))
	{
		write_expanded(line, fd[1], data);
		free(line);
		line = readline("heredoc> ");
		count++;
	}
	signal(SIGINT, SIG_DFL);
	if (line == NULL)
		mess_heredoc(redirs, count);
	free(line);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:04:30 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/14 15:54:07 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_heredoc(int fd[2], t_data *data)
{
	close(fd[0]);
	close(fd[1]);
	clean(NULL, data, 0);
}

static int	print_heredoc(char *line, int fd[2], t_data *data)
{
	char	*expand;
	char	*new;

	expand = ft_strdup(line);
	new = expand_str(expand, data);
	ft_printf_fd(fd[1], "%s", new);
	free(new);
	return (0);
}

static void	read_heredoc(char *eof, int fd[2], t_data *data)
{
	char	*scan;
	char	*nl;

	nl = ft_strjoin(eof, "\n");
	ft_printf_fd(1, "heredoc> ");
	scan = get_next_line(0);
	while (scan && ft_strcmp(scan, nl) != 0)
	{
		print_heredoc(scan, fd, data);
		ft_printf_fd(1, "heredoc> ");
		free(scan);
		scan = get_next_line(0);
		if (!scan || ft_strcmp(scan, nl) == 0)
			break ;
	}
	free(nl);
	free(scan);
}

int	heredoc_redir(char *eof, t_data *data)
{
	int		fd[2];
	int		signal;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		sigaction(SIGINT, &data->sig_child_int, 0);
		sigaction(SIGQUIT, &data->sig_child_quit, 0);
		read_heredoc(eof, fd, data);
		ft_printf_fd(fd[1], "\0");
		exit_heredoc(fd, data);
	}
	else
	{
		waitpid(pid, &signal, 0);
		write(1, "\n", 1);
		close(fd[1]);
		if (dup2(fd[0], 0) < 0)
			return (close(fd[0]), 1);
		if (WIFEXITED(signal))
			return (close(fd[0]), WEXITSTATUS(signal));
	}
	return (close(fd[0]), 0);
}

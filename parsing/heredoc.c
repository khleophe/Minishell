/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:04:30 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/23 14:50:18 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_heredoc(t_data *data)
{
	close(data->heredoc_fd[0]);
	data->heredoc_fd[0] = -1;
	close(data->heredoc_fd[1]);
	data->heredoc_fd[1] = -1;
	clean(NULL, data, 0);
}

static int	print_heredoc(char *line, t_data *data)
{
	char	*expand;
	char	*new;

	expand = ft_strdup(line);
	new = expand_str(expand, data);
	ft_printf_fd(data->heredoc_fd[1], "%s", new);
	free(new);
	return (0);
}

static void	read_heredoc(char *eof, t_data *data)
{
	char	*scan;
	char	*nl;

	nl = ft_strjoin(eof, "\n");
	ft_printf_fd(2, "heredoc> ");
	scan = get_next_line(0, nl);
	while (scan && ft_strcmp(scan, eof) != 0)
	{
		print_heredoc(scan, data);
		ft_printf_fd(2, "heredoc> ");
		free(scan);
		scan = get_next_line(0, nl);
		if (!scan || ft_strcmp(scan, nl) == 0)
			break ;
	}
	free(nl);
	free(scan);
}

// static void	read_heredoc(char *eof, t_data *data)
// {
// 	char	*scan;

// 	ft_printf_fd(2, "heredoc> ");
// 	scan = readline("");
// 	while (scan && ft_strcmp(scan, eof) != 0)
// 	{
// 		print_heredoc(scan, data);
// 		ft_printf_fd(2, "heredoc> ");
// 		free(scan);
// 		scan = readline("");
// 	}
// 	free(scan);
// }

int	heredoc_redir(char *eof, t_data *data)
{
	int		signal;
	pid_t	pid;

	pipe(data->heredoc_fd);
	pid = fork();
	if (!pid)
	{
		sigaction(SIGINT, &data->sig_child_int, 0);
		sigaction(SIGQUIT, &data->sig_child_quit, 0);
		read_heredoc(eof, data);
		ft_printf_fd(data->heredoc_fd[1], "\0");
		exit_heredoc(data);
	}
	else
	{
		waitpid(pid, &signal, 0);
		close(data->heredoc_fd[1]);
		data->heredoc_fd[1] = -1;
		if (dup2(data->heredoc_fd[0], 0) < 0)
			return (close(data->heredoc_fd[0]), data->heredoc_fd[0] = -1, 1);
		if (WIFEXITED(signal))
			return (close(data->heredoc_fd[0]), data->heredoc_fd[0] = -1,
				WEXITSTATUS(signal));
	}
	return (close(data->heredoc_fd[0]), data->heredoc_fd[0] = -1, 0);
}

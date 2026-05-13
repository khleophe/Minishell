/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:09:36 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/21 14:40:52 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir_in(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd ("minishell: ", 2);
		ft_putstr_fd(redirs->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	verif_dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_redirs_out(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirs->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	verif_dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_redirs_append(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirs->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	verif_dup2(fd, STDOUT_FILENO);
	close(fd);
}

// manquera la redirection pour heredoc(plus compliqué)
void	apply_redirs(t_redir *redirs, t_data *data)
{
	while (redirs != NULL)
	{
		if (redirs->type == REDIR_IN)
			handle_redir_in(redirs);
		else if (redirs->type == REDIR_OUT)
			handle_redirs_out(redirs);
		else if (redirs->type == APPEND)
			handle_redirs_append(redirs);
		else if (redirs->type == HEREDOC)
			handle_redir_heredoc(redirs, data);
		redirs = redirs->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 16:51:30 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/05 11:24:15 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	file_check(char *fd_arg, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(fd_arg, O_RDONLY, 0777);
	else if (mode == 1)
		fd = open(fd_arg, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else
		fd = open(fd_arg, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(fd_arg, 2);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		if (mode == 0)
			return (-1);
		return (-1);
	}
	return (fd);
}

static int	input_redir(char *file, t_redirections *r)
{
	int	fd;

	fd = file_check(file, 0);
	if (fd < 0)
		return (fd * -1);
	if (r->infd > 0)
		close(r->infd);
	r->infd = fd;
	r->in_mode = IN_FILE;
	return (0);
}

static int	output_redir(char *file, t_redirections *r)
{
	int	fd;

	fd = file_check(file, 2);
	if (fd < 0)
		return (fd * -1);
	if (r->outfd > 1)
		close(r->outfd);
	r->outfd = fd;
	r->out_mode = OUT_OVERWRITE;
	return (0);
}

static int	append_redir(char *file, t_redirections *r)
{
	int	fd;

	fd = file_check(file, 1);
	if (fd < 0)
		return (fd * -1);
	if (r->outfd > 1)
		close(r->outfd);
	r->outfd = fd;
	r->out_mode = OUT_APPEND;
	return (0);
}

int		apply_redir(t_redirections *r)
{
	if (r->in_mode != DEFAULT)
	{
		if (dup2(r->infd, STDIN_FILENO) < 0)
			return (1);
		close(r->infd);
	}
	if (r->out_mode != DEFAULT)
	{
		if (dup2(r->outfd, STDOUT_FILENO) < 0)
			return (1);
		close(r->outfd);
	}
	return (0);
}

int	create_redirs(t_token *tokens, t_redirections *r)
{
	t_token	*tmp;
	int		ret;

	ret = 0;
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redirs(tmp->type))
		{
			if (tmp->type == APPEND)
				ret = append_redir(tmp->next->s, r);
			else if (tmp->type == REDIR_IN)
				ret = input_redir(tmp->next->s, r);
			else if (tmp->type == REDIR_OUT)
				ret = output_redir(tmp->next->s, r);
			else if (tmp->type == HEREDOC)
			{
				ret = heredoc_redir(tmp->next->s, get_data());
				if (r->infd > 0)
					close(r->infd);
				r->infd = get_data()->heredoc_fd[0];
				r->in_mode = IN_HEREDOC;
			}
		}
		tmp = tmp->next;
	}
	return (ret);
}

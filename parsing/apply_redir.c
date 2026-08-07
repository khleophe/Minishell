/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:46:53 by jdelmott          #+#    #+#             */
/*   Updated: 2026/08/07 04:25:10 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redir(t_redirections *r)
{
	if (r->in_mode != DEFAULT)
	{
		if (dup2(r->infd, STDIN_FILENO) < 0)
			return (1);
		close(r->infd);
		r->infd = 0;
		r->in_mode = DEFAULT;
	}
	if (r->out_mode != DEFAULT)
	{
		if (dup2(r->outfd, STDOUT_FILENO) < 0)
			return (1);
		close(r->outfd);
		r->outfd = 1;
		r->out_mode = DEFAULT;
	}
	return (0);
}

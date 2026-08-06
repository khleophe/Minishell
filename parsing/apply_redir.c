/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:46:53 by jdelmott          #+#    #+#             */
/*   Updated: 2026/08/06 18:47:38 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redir(t_redirections *r)
{
	if (r->in_mode != DEFAULT)
	{
		if (dup2(r->infd, STDIN_FILENO) < 0)
			return (1);
	}
	if (r->out_mode != DEFAULT)
	{
		if (dup2(r->outfd, STDOUT_FILENO) < 0)
			return (1);
		close(r->outfd);
	}
	return (0);
}

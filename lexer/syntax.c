/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:31:00 by sdabbas           #+#    #+#             */
/*   Updated: 2026/05/06 15:38:37 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirs(int type)
{
	if (type == APPEND || type == HEREDOC || type == REDIR_IN
		|| type == REDIR_OUT)
		return (1);
	else
		return (0);
}
int	check_syntax(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	if (!tmp)
		return (0);
	if (tmp->type == PIPE)
		return (1);
	while (tmp)
	{
		if (is_redirs(tmp->type))
		{
			if (tmp->next == NULL || is_redirs(tmp->next->type)
				|| tmp->next->type == PIPE)
				return (1);
		}
		if (tmp->type == PIPE)
		{
			if (tmp->next == NULL || tmp->next->type == PIPE)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
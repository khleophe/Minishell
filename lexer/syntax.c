/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:31:00 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/24 17:00:26 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirs(int type)
{
	if (type == APPEND || type == HEREDOC || type == REDIR_IN
		|| type == REDIR_OUT)
		return (1);
	else
		return (0);
}

static void	count_pipe(t_data *data)
{
	t_token	*tmp;
	
	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
			data->pipe_nb++;
		tmp = tmp->next;
	}
}

int	check_syntax(t_data *data)
{
	t_token *tmp;

	tmp = data->tokens;
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
	count_pipe(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:27:13 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/25 20:38:05 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_data *data)
{
	t_token	*tmp;
	int		i;
	int		status;

	data->pipe_done = 0;
	tmp = data->tokens;
	ft_memset(data->children, 0, sizeof(data->children));
	while (data->pipe_done < data->pipe_nb)
	{
		data->return_code = parsing_cmd(data, tmp);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		if (data->return_code != 0)
			return (data->return_code);
		data->pipe_done++;
	}
	data->return_code = parsing_cmd(data, tmp);
	i = 0;
	status = 0;
	while (i < data->pipe_nb)
	{
		waitpid(data->children[i], &status, 0);
		if (WIFEXITED(status))
			data->return_code = WEXITSTATUS(status);
		i++;
	}
	return (data->return_code);
}

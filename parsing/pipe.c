/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:27:13 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/06 17:33:17 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_all(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (data->one_built == 0 && i <= data->pipe_nb)
	{
		waitpid(data->children[i], &status, 0);
		if (WIFEXITED(status))
			data->return_code = WEXITSTATUS(status);
		i++;
	}
}

int	exec_pipe(t_data *data)
{
	t_token	*tmp;
	int		return_code;

	return_code = 0;
	data->pipe_done = 0;
	tmp = data->tokens;
	ft_memset(data->children, 0, sizeof(data->children));
	while (data->pipe_done < data->pipe_nb)
	{				
		data->return_code = parsing_cmd(data, tmp, return_code);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		if (data->return_code != 0)
			return (data->return_code);
		data->pipe_done++;
	}
	return_code = 0;
	data->return_code = parsing_cmd(data, tmp, return_code);
	wait_all(data);
	return (data->return_code);
}

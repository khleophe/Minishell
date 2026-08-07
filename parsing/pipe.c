/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:27:13 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/07 04:25:25 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(t_data *data)
{
	int	i;
	int	status;
	int	ctrl_c;

	i = 0;
	status = 0;
	if (data->return_code == 130)
		ctrl_c = data->return_code;
	else
		ctrl_c = 0;
	while (data->one_built == 0 && i <= data->pipe_nb)
	{
		waitpid(data->children[i], &status, 0);
		if (WIFEXITED(status))
			data->return_code = WEXITSTATUS(status);
		i++;
	}
	if (ctrl_c == 130)
		data->return_code = 130;
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
		if (data->stdin_open == 0)
			return (data->return_code);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		data->pipe_done++;
	}
	return_code = 0;
	data->return_code = parsing_cmd(data, tmp, return_code);
	return (data->return_code);
}

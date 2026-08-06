/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 16:52:50 by jdelmott          #+#    #+#             */
/*   Updated: 2026/08/06 14:45:17 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_data *data)
{
	if (!getcwd(data->current_dir, 4096))
	{
		ft_putstr_fd("error: getcwd\n", 2);
		return (1);
	}
	return (0);
}

int	parsing_pwd(t_data *data, t_token **tokens)
{
	ft_printf_fd(1, "%s\n", data->current_dir);
	while ((*tokens) && (*tokens)->type == WORD)
		(*tokens) = (*tokens)->next;
	return (0);
}

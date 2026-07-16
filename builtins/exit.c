/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:57:04 by soraya            #+#    #+#             */
/*   Updated: 2026/07/16 14:29:44 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_exit(t_data *data, t_token **tokens)
{
	(*tokens) = (*tokens)->next;
	ft_printf_fd(2, "exit\n");
	if (!(*tokens) || (*tokens)->type != WORD)
		exit(0);
	if ((*tokens)->next && (*tokens)->next->type == WORD)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (ft_atol((*tokens)->s) == EXIT_FAILURE)
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			(*tokens)->s);
		clean(NULL, data, 2);
	}
	clean(NULL, data, ft_atol((*tokens)->s) % 256);
	return (0);
}

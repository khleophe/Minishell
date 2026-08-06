/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:57:04 by soraya            #+#    #+#             */
/*   Updated: 2026/08/07 00:13:33 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_exit(t_data *data, t_token **tokens, t_redirections *r)
{
	(*tokens) = (*tokens)->next;
	if (data->pipe_nb == 0)
		ft_printf_fd(1, "exit\n");
	if (!(*tokens) || (*tokens)->type != WORD)
	{
		clean_redirs(r);
		clean(NULL, data, data->return_code);
	}
	if (*tokens && (*tokens)->next && (*tokens)->next->type == WORD)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (*tokens && ft_atol((*tokens)->s) == EXIT_FAILURE)
	{
		ft_putstr_fd("minishell: exit: : numeric argument required\n", 2);
		clean(NULL, data, 2);
	}
	clean_redirs(r);
	clean(NULL, data, ft_atol((*tokens)->s) % 256);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:57:58 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/16 11:09:21 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean(char *str, t_data *data, int return_code)
{
	if (data->old_stdin != -1)
		close(data->old_stdin);
	if (data->old_stdout != -1)
		close(data->old_stdout);
	if (data->heredoc_fd[0] != -1)
		close(data->heredoc_fd[0]);
	if (data->heredoc_fd[1] != -1)
		close(data->heredoc_fd[1]);
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->env)
		ft_freetab(data->env);
	if (str)
		ft_printf_fd(2, "%s\n", str);
	free(data);
	close(0);
	close(1);
	close(2);
	exit(return_code);
}

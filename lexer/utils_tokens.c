/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:42:19 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/06 21:05:08 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = NULL;
	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->is == 1 && tokens->s)
			free(tokens->s);
		if (tokens)
			free(tokens);
		tokens = tmp;
	}
	tokens = NULL;
}

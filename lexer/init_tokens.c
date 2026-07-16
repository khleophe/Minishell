/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:40:45 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/16 11:22:42 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		clean("error: malloc", get_data(), 1);
	token->type = type;
	token->s = ft_strdup(value);
	if (!token->s)
		clean("error: malloc", get_data(), 1);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*current;

	if (!new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new;
}

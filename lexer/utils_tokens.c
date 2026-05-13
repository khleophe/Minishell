/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:42:19 by sdabbas           #+#    #+#             */
/*   Updated: 2026/05/06 13:24:57 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *list)
{
	t_token *tmp = NULL;

	if (!list)
		return ;
	while (list)
	{
		tmp = list->next;
		free(list->s);
		free(list);
		list = tmp;
	}
	list = NULL;
}
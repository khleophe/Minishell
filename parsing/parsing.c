/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:41:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/23 13:40:42 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing_cmd(t_data *data, t_token *tokens)
{
    while (tokens && tokens->type != PIPE)
    {
        if (tokens->type == WORD)
        {
            exec(data, tokens);
            while (tokens && tokens->type == WORD)
                tokens = tokens->next;
        }
        else
            tokens = tokens->next;
    }
    return (0);
}
int parsing(t_data *data)
{
    t_token *tmp;

    tmp = data->tokens;
    if (data->pipe_nb)
        ;
    else
    {
        return (parsing_cmd(data, tmp));
    }
    return (0);
}

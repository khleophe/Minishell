/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:41:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/24 15:53:37 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing_cmd(t_data *data, t_token *tokens)
{
    int return_code;

    return_code = 0;
    while (tokens && tokens->type != PIPE)
    {
        if (tokens->type == WORD)
        {
            return_code = exec(data, tokens);
            while (tokens && tokens->type == WORD)
                tokens = tokens->next;
        }
        else
            tokens = tokens->next;
    }
    return (return_code);
}

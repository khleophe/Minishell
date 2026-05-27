/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:41:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/05/27 15:08:29 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing(t_data *data)
{
    t_token *tmp;

    tmp = data->tokens;
    if (data->pipe_nb)
        ;
    else
    {
        
    }
}

int parsing_cmd(t_data *data, t_token *tokens)
{
    while (tokens)
    {
        if (tokens->type == WORD)
            ;
        tokens = tokens->next;
    }
}
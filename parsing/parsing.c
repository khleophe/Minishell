/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:41:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/29 17:22:42 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing_builtin(t_data *data, t_token **token)
{
    if (ft_strcmp((*token)->s, "env") == 0)
        return (parsing_env(data, token));
    else
        return (0);
}

int parsing_cmd(t_data *data, t_token *tokens)
{
    int return_code;

    return_code = 0;
    if (apply_redirs(tokens, &return_code, data))
        return (return_code);    
    while (tokens && tokens->type != PIPE)
    {
        if (is_redirs(tokens->type))
            tokens = tokens->next->next;
        if (tokens->type == WORD)
        {
            return_code = parsing_builtin(data, &tokens);
            if (tokens && tokens->type == WORD)
                return_code = exec(data, tokens);
            while (tokens && tokens->type == WORD)
                tokens = tokens->next;
        }
        else
            tokens = tokens->next;
    }
    return (return_code);
}

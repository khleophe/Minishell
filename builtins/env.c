/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 16:37:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/03 17:17:04 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void env_builtin(t_data *data)
{
    int i;

    i = 0;
    while (data->env[i])
    {
        if (ft_strchr(data->env[i], '='))
            ft_printf_fd(1, "%s\n", data->env[i]);
        i++;
    }
}

int parsing_env(t_data *data, t_token **tokens)
{
    t_token *tmp;

    tmp = (*tokens)->next;
    if ((tmp) && tmp->type == WORD)
    {
        (*tokens) = (*tokens)->next;
        return (0);
    }
    env_builtin(data);
    (*tokens) = (*tokens)->next;
    return (0);
}

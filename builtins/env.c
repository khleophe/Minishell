/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 16:37:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/02 15:21:39 by sdabbas          ###   ########.fr       */
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

int parsing_env(t_data *data, t_token **token)
{
    t_token *tmp;

    tmp = (*token)->next;
    if ((tmp) && tmp->type == WORD)
    {
        (*token) = (*token)->next;
        return (0);
    }
    env_builtin(data);
    (*token) = (*token)->next;
    return (0);
}

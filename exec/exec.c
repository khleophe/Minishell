/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:11:19 by sdabbas           #+#    #+#             */
/*   Updated: 2026/05/27 15:22:43 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_args(t_token *tokens)
{
    t_token *tmp;
    int     count;

    tmp = tokens;
    count = 0;
    if (tmp)
    {
        while (tmp && tmp->type == WORD)
            count++;
    }
    return (count);
}

char    **create_cmd(t_token *tokens)
{
    char    **cmd;
    int     len;

    len = count_args(tokens);
    cmd = malloc(sizeof(char *) * len);
    if (!cmd)

}

int exec(t_data *data, t_token *tokens)
{
    char    **cmd;
}
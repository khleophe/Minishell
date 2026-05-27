/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:11:19 by sdabbas           #+#    #+#             */
/*   Updated: 2026/05/27 15:50:39 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_args(t_token *tokens)
{
    t_token *tmp;
    int     count;

    tmp = tokens;
    count = 0;
    if (tmp)
    {
        while (tmp && tmp->type == WORD)
        {
            count++;
            tmp = tmp->next;
        }
    }
    return (count);
}

static char    **create_cmd(t_token *tokens)
{
    char    **cmd;
    int     len;
    t_token *tmp;
    int      i;

    i = 0;
    tmp = tokens;
    len = count_args(tokens);
    cmd = malloc(sizeof(char *) * len);
    if (!cmd)
        return (NULL);
    while (tmp && tmp->type == WORD && i < len)
    {
        cmd[i] = ft_strdup(tmp->s);
        if (!cmd[i])
            return (ft_freetab(cmd), NULL);
        i++;
        tmp = tmp->next;
    }
    return (cmd);
}

int exec(t_data *data, t_token *tokens)
{
    char    **cmd;

    (void)data;
    cmd = create_cmd(tokens);
    if (!cmd)
        return (1);
    for (int i = 0; cmd[i]; i++)
        printf("%s ", cmd[i]);
    printf("\n");
    printf("%s\n", find_path(cmd[0], data->env));
    ft_freetab(cmd);
    return (0);
}
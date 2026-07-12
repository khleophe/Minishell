/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soraya <soraya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:19:13 by soraya            #+#    #+#             */
/*   Updated: 2026/07/12 20:13:00 by soraya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_n(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    if (str[i] != '-')
        return (0);
    while (str[i])
    {
        i++;
        if (str[i] && str[i] != 'n')
            return (0);
    }
    return (1);
}

static void echo(t_token **tokens)
{
    while ((*tokens) && is_redirs((*tokens)->type))
        (*tokens) = (*tokens)->next->next;
    if ((*tokens) && (*tokens)->type == WORD)
    {
        ft_printf_fd(1, "%s ", (*tokens)->s);
        (*tokens) = (*tokens)->next;
    }
}

int parsing_echo(t_token **tokens)
{
    int is_n;

    is_n= 0;
    (*tokens) = (*tokens)->next;
    while ((*tokens) && is_redirs((*tokens)->type))
        (*tokens) = (*tokens)->next->next;
    while ((*tokens) && check_n((*tokens)->s))
    {
        is_n = 1;
        (*tokens) = (*tokens)->next;
    }
    while ((*tokens) && (*tokens)->type != PIPE)
        echo(tokens);
    if (is_n == 0)
        ft_printf_fd(1, "\n");
    return (0);
}
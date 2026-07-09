/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soraya <soraya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:57:04 by soraya            #+#    #+#             */
/*   Updated: 2026/07/09 19:16:38 by soraya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// numeric argument require exit 255
// exit pas dans le cas ou y'a trop d'arguments

int   parsing_exit(t_token **tokens)
{
    (*tokens) = (*tokens)->next;
    ft_printf_fd(2, "exit\n");
    if (!(*tokens) || (*tokens)->type != WORD)
        exit (0);
    if ((*tokens)->next && (*tokens)->next->type == WORD)
    {
        ft_printf_fd(2, "too many arguments\n");
        exit (1);
    }
    exit(ft_atol((*tokens)->s) % 256);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soraya <soraya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:26:31 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/09 19:22:37 by soraya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_line(char *str)
{
    if (!str[0] || str[0] == '\n')
    {
        return (0);
    }
	return (1);
}

void    read_line(t_token **tokens, t_data *data)
{
    char    *line;

    while (1)
    {
        get_pwd(data);
        data->pipe_nb = 0;
        line = readline("minishell>");
        if (line == NULL)
            exit (1);
        if (verif_line(line))
        {
            flag = 1;
            add_history(line);
            *tokens = lexer(line);
            if (check_syntax(data))
            {
                ft_printf("syntax error\n");
                data->return_code = 2;
                free_tokens(*tokens);
                *tokens = NULL;
            }
            else 
            {
                expand_all_tokens(*tokens, data);
                if (tokens)
                    exec_pipe(data);
                dup2(data->old_stdin, STDIN_FILENO);
                dup2(data->old_stdout, STDOUT_FILENO);//a secu lol
                free_tokens(*tokens);
                *tokens = NULL;
            }
        }
        flag = 0;
        free(line);
    }
}

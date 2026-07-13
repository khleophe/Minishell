/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:26:31 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/13 14:15:51 by sdabbas          ###   ########.fr       */
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
 
    get_pwd(data);
    while (1)
    {      
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

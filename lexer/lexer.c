/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:26:31 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/23 13:34:21 by sdabbas          ###   ########.fr       */
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

/*void    exec_command(char *str, t_data *data)
{
	char	**ret;
	int		pid;

    ret = ft_split(str, ' ');
    if (!ret)
        return ;
    if (ret[0] == NULL)
        ft_freetab(ret);
    pid = fork();
    if (pid == - 1)
        exit(1);
    else if (pid == 0)
    {
        execve("/bin/ls", ret, data->env);
        ft_freetab(ret);
        exit (127);
    }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);
        ft_freetab(ret);
    }
}*/

void    read_line(t_token **tokens, t_data *data)
{
    char    *line;
    // t_token *tmp;

    while (1)
    {
        data->pipe_nb = 0;
        line = readline("minishell>");
        if (line == NULL)
            exit (1);
        if (verif_line(line))
        {
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
                // tmp = *tokens;
                // while (tmp)
                // {
                //     printf("%i, %s\n", tmp->type, tmp->s);
                //     tmp = tmp->next;
                // }
                if (tokens)
                    exec_pipe(data);
                free_tokens(*tokens);
                *tokens = NULL;
            }
            /*if (tokens)
            {
                parser + exec ;
                free_tokens(tokens);
                tokens = NULL;
            }*/
        }
        free(line);
    }
}

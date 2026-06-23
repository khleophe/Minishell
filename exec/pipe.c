/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:27:13 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/23 14:56:51 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exit_pipe(t_token *token, int pipe_fd[2], int return_value, char *s)
{
    if (s != NULL)
        ft_printf("%s", s);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free_tokens(token);
    exit(return_value);
}

//int parsing_tt_court
//parsing_redir
//whild (token->type == REDIR)
//   token = token->next
//parsing_cmd
//
//

static int create_child(t_data *data, t_token **token)
{
    int pipe_fd[2];
    pid_t pid;
    
    pipe(pipe_fd);
    pid = fork();
    if (!pid)
    {
        if (dup2(pipe_fd[1], 1) < 0)
            exit_pipe((*token), pipe_fd, 1, "error dup2\n");
        parsing_cmd(data, (*token));
        exit_pipe((*token), pipe_fd, 0, NULL);
    }
    else
    {
        if (dup2(pipe_fd[0], 0) < 0)
            exit_pipe((*token), pipe_fd, 1, "error dup2\n");
        while ((*token) && (*token)->type != PIPE)
            (*token) = (*token)->next;
        if ((*token)->next && (*token)->type == PIPE)
            (*token) = (*token)->next;
    }
    return(close(pipe_fd[0]), close(pipe_fd[1]), 0);
}

int exec_pipe(t_data *data)
{
    int pipeddone;
    t_token *tmp = data->tokens;

    pipeddone = 0;
    while (pipeddone < data->pipe_nb)
    {
        create_child(data, &tmp);       
        pipeddone++;
    }
    // printf("pipe_nb = %i\n", data->pipe_nb);
    return (parsing_cmd(data, tmp));
}
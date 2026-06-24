/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:27:13 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/24 15:55:13 by sdabbas          ###   ########.fr       */
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
    token = NULL;
    exit(return_value);
}

static pid_t create_child(t_data *data, t_token **token, int last, int *fd_in)
{
    int pipe_fd[2];
    int return_code;
    pid_t pid;

    if (last > 0)
        pipe(pipe_fd);
    pid = fork();
    if (pid == 0)
    {            
        if (*fd_in != 0)
        {
            dup2(*fd_in, 0);
            close(*fd_in);
        }
        if (last > 0)
        {
            if (dup2(pipe_fd[1], 1) < 0)
                exit_pipe((*token), pipe_fd, 1, "error dup2\n");
        }
        return_code = parsing_cmd(data, (*token));
        exit_pipe((*token), pipe_fd, return_code, NULL);
    }
    else
    {
        if (last > 0)
        {
            *fd_in = pipe_fd[0];
            close(pipe_fd[1]);
        }
        while ((*token) && (*token)->type != PIPE)
            (*token) = (*token)->next;
        if ((*token) && (*token)->type == PIPE)
            (*token) = (*token)->next;
    }
    return(pid);
}

static int  get_return_code(pid_t pid)
{
    pid_t last_pid;
    int status;
    int return_code;

    return_code = 0;
    last_pid = wait(&status);
    while (last_pid > 0)
    {
        if (last_pid == pid)
        {
            if (WIFEXITED(status))
                return_code = (WEXITSTATUS(status));
        }
        last_pid = wait(&status);
    }
    return (return_code);
}

int exec_pipe(t_data *data)
{
    int pipeddone;
    t_token *tmp = data->tokens;
    int fd_in;
    pid_t last_pid;
    
    fd_in = 0;
    pipeddone = 0;
    while (pipeddone <= data->pipe_nb)
    {
        last_pid = create_child(data, &tmp, data->pipe_nb - pipeddone, &fd_in);
        pipeddone++;
    }
    data->return_code = get_return_code(last_pid);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:04:30 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/29 16:20:08 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// signaux avec Marius + ne marche pas avec les pipes

static int  print_heredoc(char *line, int fd[2], t_data *data)
{
    char    *expand;
    char    *new;
    
    expand = ft_strjoin(line, "\n");
    new = expand_str(expand, data);
    ft_printf_fd(fd[1], "%s", new);
    free(new);
    return (0);
}

int heredoc_redir(char *eof, t_data *data)
{
    char    *line;
    int     fd[2];
    int     signal;
    pid_t   pid;

    pipe(fd);
    pid = fork();
    if (!pid)
    {
        close(fd[0]);
        line = readline("heredoc> ");
        while (line && ft_strcmp(line, eof) != 0)
        {
            print_heredoc(line, fd, data);
            free(line);
            line = readline("heredoc> ");
        }
        free(line);
        ft_printf_fd(fd[1], "\0");
        close(fd[1]);
        exit (0);
    }
    else
    {
        waitpid(pid, &signal, 0);
        close(fd[1]);
        if (dup2(fd[0], 0) < 0)
            return (close(fd[0]), close(fd[1]), 1);
        close(fd[0]);
        if (WIFEXITED(signal))
            return (WEXITSTATUS(signal));
    }
    return (0);
}
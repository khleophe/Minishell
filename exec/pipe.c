/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:27:13 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/23 16:34:10 by sdabbas          ###   ########.fr       */
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
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        while ((*token) && (*token)->type != PIPE)
            (*token) = (*token)->next;
        if ((*token) && (*token)->type == PIPE)
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

/*static void exit_pipe(t_token *token, int return_value)
{
    free_tokens(token);
    exit(return_value);
}

static int create_child(t_data *data, t_token *token, int fd_in, int pipe_fd[2], int is_last)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
        return (-1);
    if (pid == 0)
    {
        // Si on a une entrée d'un pipe précédent, on la redirige sur 0
        if (fd_in != 0)
        {
            dup2(fd_in, 0);
            close(fd_in);
        }
        // Si ce n'est PAS la dernière commande, on redirige la sortie sur le pipe actuel
        if (!is_last)
        {
            dup2(pipe_fd[1], 1);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
        }
        
        // On exécute la commande dans l'enfant
        parsing_cmd(data, token);
        exit_pipe(token, 0);
    }
    return (pid);
}

int exec_pipe(t_data *data)
{
    t_token *tmp = data->tokens;
    int     pipe_fd[2];
    int     fd_in = 0;
    int     i = 0;

    // On boucle sur TOUTES les commandes (pipe_nb + 1)
    while (i <= data->pipe_nb)
    {
        // Si ce n'est pas la dernière commande, on crée un pipe
        if (i < data->pipe_nb)
            pipe(pipe_fd);

        // On fork l'enfant (on lui dit si c'est le dernier ou pas via le 5ème argument)
        create_child(data, tmp, fd_in, pipe_fd, (i == data->pipe_nb));

        // Le parent nettoie les fds obsolètes
        if (fd_in != 0)
            close(fd_in);
        if (i < data->pipe_nb)
        {
            fd_in = pipe_fd[0]; // On garde la lecture pour le prochain enfant
            close(pipe_fd[1]);  // On ferme l'écriture devenue inutile pour le parent
        }

        // On avance les tokens jusqu'au prochain pipe
        while (tmp && tmp->type != PIPE)
            tmp = tmp->next;
        if (tmp && tmp->type == PIPE)
            tmp = tmp->next;
        i++;
    }

    // UNIQUE ENDROIT OÙ LE PARENT ATTEND : On attend la fin de TOUS les enfants
    while (wait(NULL) > 0)
        ;

    return (0);
}*/
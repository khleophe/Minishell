/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 16:51:30 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/29 14:58:30 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	file_check(char *fd_arg, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(fd_arg, O_RDONLY, 0777);
	else if (mode == 1)
		fd = open(fd_arg, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else
		fd = open(fd_arg, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2); 
        ft_putstr_fd(fd_arg, 2);
        ft_putstr_fd(" ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);	
        if (mode == 0)
			return (-1);
		return (-1);
	}
	return (fd);
}

static int	input_redir(char *file)
{
	int	fd;

	fd = file_check(file, 0);
	if (fd < 0)
		return (fd * -1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (1);
	if (close(fd) < 0)
		return (1);
	return (0);
}

static int	output_redir(char *file)
{
	int	fd;

	fd = file_check(file, 2);
	if (fd < 0)
		return (fd * -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	if (close(fd) < 0)
		return (1);
	return (0);
}

static int	append_redir(char *file)
{
	int	fd;

	fd = file_check(file, 1);
	if (fd < 0)
		return (fd * -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	if (close(fd) < 0)
		return (1);
	return (0);
}

int apply_redirs(t_token *tokens, int *return_code, t_data *data)
{
    t_token *tmp;

    tmp = tokens; 
    while (tmp && tmp->type != PIPE)
    {
        if (is_redirs(tmp->type))
        {
            if (tmp->type == APPEND)
                *return_code = append_redir(tmp->next->s);
            else if (tmp->type == REDIR_IN)
                *return_code = input_redir(tmp->next->s);
            else if (tmp->type == REDIR_OUT)
                *return_code = output_redir(tmp->next->s);
            else if (tmp->type == HEREDOC)
				*return_code = heredoc_redir(tmp->next->s, data);
        }    
        tmp = tmp->next;
    }
    return (*return_code);
}


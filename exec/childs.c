/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 17:50:58 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/21 12:21:44 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mess_execve(t_cmd *cmd)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

void	mess_fork(void)
{
	perror("fork");
	exit(EXIT_FAILURE);
}

static void	execve_childs(char *path, t_cmd *cmd, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (path == NULL)
	{
		if (cmp_builtins(cmd))
			exit(init_builtins(data, cmd));
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	if (execve(path, cmd->args, data->env) == -1)
		mess_execve(cmd);
}

// sert à écrire dans le pipe
void	child_write(t_pipe *p, char *path, t_cmd *cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (p->prev_fd != -1)
		{
			verif_dup2(p->prev_fd, STDIN_FILENO);
			close(p->prev_fd);
		}
		verif_dup2(p->pipefd[1], STDOUT_FILENO);
		close(p->pipefd[0]);
		close(p->pipefd[1]);
		apply_redirs(cmd->redirs, data);
		execve_childs(path, cmd, data);
	}
	else
		close(p->pipefd[1]);
}

// sert a lire depuis le pipe, dernier enfant
void	child_read(t_pipe *p, char *path, t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		mess_fork();
	else if (pid == 0)
	{
		verif_dup2(p->pipefd[0], STDIN_FILENO);
		close(p->pipefd[0]);
		close(p->pipefd[1]);
		apply_redirs(cmd->redirs, data);
		execve_childs(path, cmd, data);
	}
	else
	{
		close(p->pipefd[0]);
		waitpid(pid, &status, 0);
		status_return_code(data, status);
		while (waitpid(-1, NULL, 0) > 0)
			;
		interactive_signals();
	}
}

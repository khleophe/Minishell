/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:50:56 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/21 12:21:09 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	status_return_code(t_data *data, int status)
{
	if (WIFSIGNALED(status))
		data->return_code = 128 + WTERMSIG(status);
	else
		data->return_code = WEXITSTATUS(status);
}

static int	fork_and_exec(char *path, t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	exec_signals();
	pid = fork();
	if (pid == 0)
	{
		apply_redirs(cmd->redirs, data);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->args, data->env);
		free(path);
		mess_execve(cmd);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (free(path), 1);
	}
	waitpid(pid, &status, 0);
	interactive_signals();
	status_return_code(data, status);
	free(path);
	return (data->return_code);
}

int	mess_execute(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

int	execute(t_cmd *cmd, t_data *data)
{
	char	*path;
	int		in;
	int		out;
	int		res;

	if (cmp_builtins(cmd) && cmd->redirs != NULL)
	{
		in = dup(STDIN_FILENO);
		out = dup(STDOUT_FILENO);
		apply_redirs(cmd->redirs, data);
		res = init_builtins(data, cmd);
		verif_dup2(in, STDIN_FILENO);
		verif_dup2(out, STDOUT_FILENO);
		close(in);
		close(out);
		return (res);
	}
	else if (cmp_builtins(cmd))
		return (init_builtins(data, cmd));
	path = find_path(cmd->args[0], data->env);
	if (!path)
		return (mess_execute(cmd));
	return (fork_and_exec(path, cmd, data));
}

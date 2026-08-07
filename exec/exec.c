/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:11:19 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/07 02:56:15 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_fail(char *path, char **cmd, t_data *data)
{
	if ((ft_strnstr(cmd[0], "/", 2) && access(&cmd[0][2], F_OK) == 0))
	{
		if (access(&cmd[0][2], F_OK | X_OK) != 0)
			ft_putstr_fd("minishell: : permission denied\n", 2);
		else
			ft_putstr_fd("minishell: : Is a directory\n", 2);
		free(path);
		ft_freetab(cmd);
		clean(NULL, data, 126);
	}
	else
	{
		if (ft_strnstr(cmd[0], "./", 2) || cmd[0][0] == '/')
			ft_putstr_fd("minishell: : No such file or directory\n", 2);
		else
			ft_putstr_fd("minishell: : command not found\n", 2);
		free(path);
		ft_freetab(cmd);
		clean(NULL, data, 127);
	}
}

int	set_stdin_stdout(t_data *data, t_redirections *r, int pipe_fd[2])
{
	if (data->current_stdin > 0)
	{
		if (dup2(data->current_stdin, 0) < 0)
			return (close(pipe_fd[0]), close(pipe_fd[1]), clean("error: dup2",
					data, 1), 1);
		close(data->current_stdin);
		data->current_stdin = 0;
	}
	if (data->pipe_nb > 0 && data->pipe_done < data->pipe_nb)
	{
		if (dup2(pipe_fd[1], 1) < 0)
			return (close(pipe_fd[0]), close(pipe_fd[1]), clean("error: dup2",
					data, 1), 1);
	}
	if (data->pipe_nb > 0 && data->pipe_done <= data->pipe_nb)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (apply_redir(r) == 1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), clean("error: dup2",
				get_data(), 1), 1);
	return (0);
}

void	reset_after_child_and_change_stdin(t_data *data, t_redirections *r,
		int pipe_fd[2], pid_t pid)
{
	clean_redirs(r);
	if (data->pipe_nb > 0 && data->pipe_done <= data->pipe_nb)
		change_current_stdin(data, pipe_fd);
	data->children[data->pipe_done] = pid;
}

static int	execute(t_data *data, char *path, char **cmd, t_redirections *r)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (data->pipe_nb > 0 && data->pipe_done <= data->pipe_nb)
		pipe(pipe_fd);
	data->one_built = 0;
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), clean("no", data, 1), 1);
	if (pid == 0)
	{
		set_stdin_stdout(data, r, pipe_fd);
		data->sig_quit.sa_handler = SIG_DFL;
		sigaction(SIGQUIT, &data->sig_quit, 0);
		if (path)
			execve(path, cmd, data->env);
		exec_fail(path, cmd, data);
		clean(NULL, get_data(), 0);
	}
	else
		reset_after_child_and_change_stdin(data, r, pipe_fd, pid);
	return (0);
}

int	exec(t_data *data, t_token **tokens, t_redirections *r)
{
	char	**cmd;
	char	*path;

	(void)data;
	cmd = create_cmd((*tokens));
	if (!cmd)
		return (1);
	path = find_path(cmd[0], data->env);
	execute(data, path, cmd, r);
	ft_freetab(cmd);
	free(path);
	return (data->return_code);
}

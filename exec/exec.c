/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:11:19 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/04 17:09:45 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_fail(char *path, char **cmd, t_data *data)
{
	if ((ft_strnstr(cmd[0], "/", 2) && access(&cmd[0][2], F_OK) == 0))
	{
		if (access(&cmd[0][2], F_OK | X_OK) != 0)
			ft_printf_fd(2, "minishell: %s: permission denied\n", cmd[0]);
		else
			ft_printf_fd(2, "minishell: %s: Is a directory\n", cmd[0]);
		free(path);
		ft_freetab(cmd);
		clean(NULL, data, 126);
	}
	else
	{
		if (ft_strnstr(cmd[0], "./", 2) || cmd[0][0] == '/')
			ft_printf_fd(2, "minishell: %s: No such file or directory\n",
				cmd[0]);
		else
			ft_printf_fd(2, "minishell: %s: command not found\n", cmd[0]);
		free(path);
		ft_freetab(cmd);
		clean(NULL, data, 127);
	}
}

static int	execute(t_data *data, char *path, char **cmd, t_redirections *r)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (data->pipe_nb > 0 && data->pipe_done <= data->pipe_nb)
		pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		if (r->in_mode)
		{
			dup2(r->infd, STDIN_FILENO);
			close(r->infd);
		}
		if (r->out_mode)
		{
			dup2(r->outfd, STDOUT_FILENO);
			close(r->outfd);
		}
		if (data->pipe_nb > 0 && data->pipe_done < data->pipe_nb)
		{
			if (dup2(pipe_fd[1], 1) < 0)
				clean("error: dup2", data, 1);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		data->sig_quit.sa_handler = SIG_DFL;
		sigaction(SIGQUIT, &data->sig_quit, 0);
		if (path)
		{
			execve(path, cmd, data->env);
			exec_fail(path, cmd, data);
		}
		clean(NULL, get_data(), 0);
	}
	else
	{
		if (r->in_mode)
			close(r->infd);
		if (r->out_mode)
			close(r->outfd);
		if (data->heredoc_fd[0] != -1)
		{
			close(data->heredoc_fd[0]);
			data->heredoc_fd[0] = -1;
		}
		if (data->pipe_nb > 0 && data->pipe_done <= data->pipe_nb)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		data->children[data->pipe_done] = pid;
	}
	// fork peut envoyer -1
	return (0);
}

static int	count_args(t_token *tokens)
{
	t_token	*tmp;
	int		count;

	tmp = tokens;
	count = 0;
	if (tmp)
	{
		while (tmp && tmp->type == WORD)
		{
			count++;
			tmp = tmp->next;
		}
	}
	return (count);
}

static char	**create_cmd(t_token *tokens)
{
	char	**cmd;
	int		len;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	len = count_args(tokens);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		clean("error: malloc", get_data(), 1);
	while (tmp && tmp->type == WORD && i < len)
	{
		cmd[i] = ft_strdup(tmp->s);
		if (!cmd[i])
			return (ft_freetab(cmd), clean("error: malloc", get_data(), 1),
				NULL);
		i++;
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
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
	execute(data, path, cmd, r); // HANDLE ERROR HERE
	ft_freetab(cmd);
	free(path);
	return (data->return_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:11:19 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/23 14:53:38 by sdabbas          ###   ########.fr       */
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

static int	execute(t_data *data, char *path, char **cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		data->sig_quit.sa_handler = SIG_DFL;
		sigaction(SIGQUIT, &data->sig_quit, 0);
		if (path)
			execve(path, cmd, data->env);
		exec_fail(path, cmd, data);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
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

int	exec(t_data *data, t_token *tokens)
{
	char	**cmd;
	char	*path;

	(void)data;
	cmd = create_cmd(tokens);
	if (!cmd)
		return (1);
	path = find_path(cmd[0], data->env);
	data->return_code = execute(data, path, cmd);
	ft_freetab(cmd);
	free(path);
	return (data->return_code);
}

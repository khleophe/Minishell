/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:11:19 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/14 15:56:18 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_fail(char *path, char **cmd, t_data *data)
{
	if (ft_strnstr(cmd[0], "/", 1))
	{
		ft_printf("minishell: %s: Is a directory\n", cmd[0]);
		free(path);
		ft_freetab(cmd);
		clean(NULL, data, 126);
	}
	else
	{
		ft_printf("%s: command not found: \n", cmd[0]);
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
		return (NULL);
	while (tmp && tmp->type == WORD && i < len)
	{
		cmd[i] = ft_strdup(tmp->s);
		if (!cmd[i])
			return (ft_freetab(cmd), NULL);
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

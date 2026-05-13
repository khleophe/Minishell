/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:51:20 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/24 16:35:51 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(t_data *data)
{
	int	i;

	i = 0;
	if (!data->env)
		return ;
	while (data->env[i] != NULL)
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = NULL;
	if (!redirs)
		return ;
	while (redirs)
	{
		tmp = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = tmp;
	}
	redirs = NULL;
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd->next;
		free_redirs(cmd->redirs);
		while (cmd->args[i] != NULL)
		{
			free(cmd->args[i]);
			i++;	
		}
		free(cmd->args);
		i = 0;
		free(cmd);
		cmd = tmp;	
	}
	cmd = NULL;
}

void	message_cd(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

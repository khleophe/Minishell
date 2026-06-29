/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:58:06 by nolwenng          #+#    #+#             */
/*   Updated: 2026/06/29 16:51:13 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	cmp_builtins(t_cmd *cmd)
// {
// 	if (!ft_strcmp(cmd->args[0], "cd")
// 		|| !ft_strcmp(cmd->args[0], "echo")
// 		|| !ft_strcmp(cmd->args[0], "env")
// 		|| !ft_strcmp(cmd->args[0], "exit")
// 		|| !ft_strcmp(cmd->args[0], "export")
// 		|| !ft_strcmp(cmd->args[0], "unset")
// 		|| !ft_strcmp(cmd->args[0], "pwd"))
// 		return (1);
// 	else
// 		return (0);
// }

// int	init_builtins(t_data *data, t_cmd *cmd)
// {
// 	int	build;

// 	if (!ft_strcmp(cmd->args[0], "echo"))
// 		build = echo_builtin(cmd);
// 	else if (!ft_strcmp(cmd->args[0], "cd"))
// 		build = cd_builtin(cmd, data);
// 	else if (!ft_strcmp(cmd->args[0], "pwd"))
// 		build = pwd_builtin();
// 	else if (!ft_strcmp(cmd->args[0], "env"))
// 		build = env_builtin(data);
// 	else if (!ft_strcmp(cmd->args[0], "export"))
// 		build = export_builtin(cmd, data);
// 	else if (!ft_strcmp(cmd->args[0], "unset"))
// 		build = unset_builtin(cmd, data);
// 	else
// 		build = exit_builtin(cmd, data);
// 	return (build);
// }

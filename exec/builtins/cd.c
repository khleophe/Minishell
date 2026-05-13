/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:56:48 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/21 11:31:04 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_null(t_data *data)
{
	char	*home;
	int		res;

	home = get_env_value("HOME", data->env);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (-1);
	}
	res = chdir(home);
	if (res == -1)
		message_cd(home);
	return (res);
}

void	update_pwd(char *old_pwd, t_data *data)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	if (old_pwd)
		update_env("OLDPWD", old_pwd, data);
	else
		update_env("OLDPWD", "", data);
	update_env("PWD", new_pwd, data);
	free(new_pwd);
}

int	cd_helper(t_data *data)
{
	char	*home;
	int		res;

	home = get_env_value("OLDPWD", data->env);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (-1);
	}
	res = chdir(home);
	if (res == -1)
		message_cd(home);
	else
	{
		ft_putstr_fd(home, 1);
		write(1, "\n", 1);
	}
	return (res);
}

int	many_args_mess(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	return (1);
}

// revenir dessus ^pour changer la maj de PWD/OLDPWD avec export
int	cd_builtin(t_cmd *cmd, t_data *data)
{
	int		res;
	char	*old_pwd;
	char	*tmp;

	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
		return (many_args_mess());
	tmp = get_env_value("PWD", data->env);
	if (tmp)
		old_pwd = ft_strdup(tmp);
	else
		old_pwd = NULL;
	if (cmd->args[1] == NULL)
		res = cd_null(data);
	else if (ft_strcmp(cmd->args[1], "-") == 0)
		res = cd_helper(data);
	else
	{
		res = chdir(cmd->args[1]);
		if (res == -1)
			message_cd(cmd->args[1]);
	}
	if (res != -1)
		update_pwd(old_pwd, data);
	free(old_pwd);
	return (res == -1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:38:52 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/13 14:39:10 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd(t_data *data, char *path)
{
	//exit en cas erreur malloc
	char	*temp;
	
	if (chdir(path) == -1)
		return (ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", path), 1);
	temp = ft_strjoin("OLDPWD=", data->current_dir);
	if (!temp)
		return (1);
	if (export(data, temp) == 1)
		return (free(temp), 1);
	free(temp);
	if (get_pwd(data) == 1)
		return (1);
	temp = ft_strjoin("PWD=", data->current_dir);
	if (!temp)
		return (1);
	if (export(data, temp) == 1)
		return (free(temp), 1);
	free(temp);
	return (0);
}

static int cd_dash(t_data *data, t_token **tokens)
{
	if (ft_strcmp((*tokens)->s, "-") == 0)
		ft_printf_fd(1, "%s\n", get_env_value("HOME", data->env));
	else if (ft_strnstr((*tokens)->s, "--", 2) && (ft_strlen((*tokens)->s) > 2))
	{
		(*tokens) = (*tokens)->next;
		return (ft_printf_fd(2, "minishell: cd: --: invalid option\n"), 2);
	}
	(*tokens) = (*tokens)->next;
	return (cd(data, get_env_value("HOME", data->env)));
}

int	parsing_cd(t_data *data, t_token **tokens)
{
	int	return_code;

	(*tokens) = (*tokens)->next;
	if (!(*tokens) || (*tokens)->type != WORD)
		return (cd(data, get_env_value("HOME", data->env)));
	if ((*tokens)->next && (*tokens)->next->type == WORD)
	{
		while ((*tokens) && (*tokens)->type == WORD)
			(*tokens) = (*tokens)->next;
		return (ft_printf_fd(2, "minishell: cd: too many arguments\n"), 1);
	} 
	if (ft_strcmp((*tokens)->s, "~") == 0 || ft_strcmp((*tokens)->s, "-") == 0 || ft_strnstr((*tokens)->s, "--", 2))
		return (cd_dash(data, tokens));
	return_code = cd(data, (*tokens)->s);
	(*tokens) = (*tokens)->next;
	return (return_code);
}

/*int	cd_null(t_data *data)
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
}*/

// revenir dessus ^pour changer la maj de PWD/OLDPWD avec export
// int	cd_builtin(t_cmd *cmd, t_data *data)
// {
// 	int		res;
// 	char	*old_pwd;
// 	char	*tmp;

// 	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
// 		return (many_args_mess());
// 	tmp = get_env_value("PWD", data->env);
// 	if (tmp)
// 		old_pwd = ft_strdup(tmp);
// 	else
// 		old_pwd = NULL;
// 	if (cmd->args[1] == NULL)
// 		res = cd_null(data);
// 	else if (ft_strcmp(cmd->args[1], "-") == 0)
// 		res = cd_helper(data);
// 	else
// 	{
// 		res = chdir(cmd->args[1]);
// 		if (res == -1)
// 			message_cd(cmd->args[1]);
// 	}
// 	if (res != -1)
// 		update_pwd(old_pwd, data);
// 	free(old_pwd);
// 	return (res == -1);
// }

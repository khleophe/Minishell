/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:38:52 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/14 15:38:14 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd(t_data *data, char *path)
{
	char	*temp;

	// exit en cas erreur malloc
	if (chdir(path) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
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

static int	cd_dash(t_data *data, t_token **tokens)
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
	if (ft_strcmp((*tokens)->s, "~") == 0 || ft_strcmp((*tokens)->s, "-") == 0
		|| ft_strnstr((*tokens)->s, "--", 2))
		return (cd_dash(data, tokens));
	return_code = cd(data, (*tokens)->s);
	(*tokens) = (*tokens)->next;
	return (return_code);
}

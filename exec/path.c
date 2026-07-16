/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 15:41:54 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/16 11:14:38 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *key, char **env)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	if (env == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

char	*path_helper(char *dir, char *cmd)
{
	char	*tmp;
	char	*join;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		clean("error: malloc", get_data(), 1);
	join = ft_strjoin(tmp, cmd);
	if (!join)
	{
		free(tmp);
		clean("error: malloc", get_data(), 1);
	}
	if (access(join, X_OK) == 0)
	{
		free(tmp);
		return (join);
	}
	free(tmp);
	free(join);
	return (NULL);
}

char	*access_path(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == -1)
			return (NULL);
		else
			return (ft_strdup(cmd));
	}
	else
		return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	int		i;
	char	*res;
	char	*path;
	char	**paths;

	i = 0;
	res = access_path(cmd);
	if (res)
		return (res);
	path = get_env_value("PATH", env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[i] != NULL)
	{
		res = path_helper(paths[i], cmd);
		if (res)
			return (ft_freetab(paths), res);
		i++;
	}
	return (ft_freetab(paths), NULL);
}

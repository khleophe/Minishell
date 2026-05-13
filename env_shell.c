/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:37:37 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/20 15:50:03 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// appeler dup_env au démarrage dans le main pour que data->env 
// soit une copie malloc'd dès le début.
//duplique l'env
char	**dup_env(char **env)
{
	char	**dup;
	int		n;

	n = 0;
	while (env[n] != NULL)
		n++;
	dup = malloc(sizeof(char *) * (n + 1));
	if (!dup)
		return (NULL);
	n = 0;
	while (env[n] != NULL)
	{
		dup[n] = ft_strdup(env[n]);
		if (!dup[n])
		{
			while (n > 0)
				free(dup[--n]);
			free(dup);
			return (NULL);
		}
		n++;
	}
	dup[n] = NULL;
	return (dup);
}

void	update_env(char *key, char *value, t_data *data)
{
	int		cd;
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	res = ft_strjoin(tmp, value);
	free(tmp);
	if (!res)
		return ;
	cd = find_index(key, data->env);
	if (cd == -1)
	{
		free(res);
		return ;
	}
	free(data->env[cd]);
	data->env[cd] = res;
}

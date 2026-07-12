/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soraya <soraya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:37:37 by nolwenng          #+#    #+#             */
/*   Updated: 2026/07/12 19:03:56 by soraya           ###   ########.fr       */
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


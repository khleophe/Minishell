/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:56:58 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/20 00:01:02 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(char **sorted, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	export_no_args(t_data *data)
{
	int		i;
	int		n;
	char	**sorted;

	n = 0;
	while (data->env[n] != NULL)
		n++;
	sorted = malloc(sizeof(char *) * (n + 1));
	if (!sorted)
		return ;
	i = 0;
	while (i < n)
	{
		sorted[i] = data->env[i];
		i++;
	}
	sorted[n] = NULL;
	sort_env(sorted, n);
	i = 0;
	while (sorted[i] != NULL)
		print_export(sorted[i++]);
	free(sorted);
}

int	export_no_value(char *args, t_data *data, int *n)
{
	char	**tmp;

	if (find_index(args, data->env) == -1)
	{
		tmp = realloc(data->env, sizeof(char *) * (*n + 2));
		if (!tmp)
			return (0);
		data->env = tmp;
		data->env[*n] = ft_strdup(args);
		if (data->env[*n] == NULL)
			return (1);
		data->env[*n + 1] = NULL;
		(*n)++;
	}
	return (1);
}

int	count_env(t_data *data)
{
	int	n;

	n = 0;
	while (data->env[n] != NULL)
		n++;
	return (n);
}

int	export_builtin(t_cmd *cmd, t_data *data)
{
	int		i;
	int		n;

	i = 1;
	if (cmd->args[1] == NULL)
		return (export_no_args(data), 0);
	n = count_env(data);
	while (cmd->args[i] != NULL)
	{
		if (export_error(cmd->args[i], data))
		{
			i++;
			continue ;
		}
		if (ft_strchr(cmd->args[i], '=') == NULL)
		{
			if (export_no_value(cmd->args[i], data, &n) == 0)
				return (0);
			i++;
			continue ;
		}
		export_helper(cmd->args[i], data, &n);
		i++;
	}
	return (0);
}

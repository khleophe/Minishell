/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:26:53 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/20 22:06:37 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_existing(char *arg, t_data *data, int idx)
{
	char	*dup;

	dup = ft_strdup(arg);
	if (!dup)
		return (0);
	free(data->env[idx]);
	data->env[idx] = dup;
	return (1);
}

static int	create_var(char *arg, t_data *data, int *n)
{
	char	**tmp;

	tmp = realloc(data->env, sizeof(char *) * (*n + 2));
	if (!tmp)
		return (0);
	data->env = tmp;
	data->env[*n] = ft_strdup(arg);
	if (!data->env[*n])
		return (0);
	data->env[*n + 1] = NULL;
	(*n)++;
	return (1);
}

void	export_helper(char *arg, t_data *data, int *n)
{
	int		idx;
	int		pos_len;
	char	*pos;

	pos = ft_strchr(arg, '=');
	pos_len = pos - arg;
	pos = ft_substr(arg, 0, pos_len);
	if (!pos)
		return ;
	idx = find_index(pos, data->env);
	free(pos);
	if (idx != -1)
		update_existing(arg, data, idx);
	else
		create_var(arg, data, n);
}

int	is_valid_id(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[0]) || arg[0] == '_')
		i++;
	else
		return (0);
	i = 1;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export_error(char *arg, t_data *data)
{
	if (!is_valid_id(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		data->return_code = 1;
		return (1);
	}
	return (0);
}

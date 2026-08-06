/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 15:38:54 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/06 21:21:28 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	already_exist(t_data *data, char *arg)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_substr(arg, 0, is_dash(arg));
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], temp, ft_strlen(temp)))
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(arg);
			return (free(temp), 1);
		}
		i++;
	}
	if (temp)
		free(temp);
	return (0);
}

static int	add_arg(t_data *data, char *arg)
{
	char	**temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char *) * (print_export(data, 0) + 2));
	if (!temp)
		return (1);
	while (data->env[i])
	{
		temp[i] = ft_strdup(data->env[i]);
		if (!temp[i])
			return (ft_freetab(temp), 1);
		i++;
	}
	ft_freetab(data->env);
	temp[i] = ft_strdup(arg);
	i++;
	temp[i] = NULL;
	data->env = ft_splitdup(temp);
	ft_freetab(temp);
	return (0);
}

int	export(t_data *data, char *arg)
{
	if (!data->env)
		return (ft_putstr_fd("error: export: no env\n", 2), 1);
	if (already_exist(data, arg))
		return (0);
	return (add_arg(data, arg));
}

int	parsing_export(t_data *data, t_token **tokens)
{
	int	return_code;

	return_code = 0;
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || (*tokens)->type == PIPE)
		return (print_export(data, 1), 0);
	while ((*tokens) && (*tokens)->type == WORD)
	{
		if (verif_args_export((*tokens)->s))
		{
			if (export(data, (*tokens)->s) == 1)
				return (1);
		}
		else
			return_code = 2;
		(*tokens) = (*tokens)->next;
	}
	return (return_code);
}

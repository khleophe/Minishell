/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 18:08:09 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/24 18:26:59 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utils_expand(char *s, int i, int len, t_expand *ex)
{
	if (len > 1)
	{
		ex->key = ft_substr(s, i + 1, len - 1);
		ex->post = ft_strdup(s + i + len);
	}
	else
	{
		ex->key = ft_substr(s, i + 1, len);
		ex->post = ft_strdup(s + i + len + 1);
	}
	if (ex->key == NULL || ex->post == NULL)
	{
		if (ex->post)
		{
			free(ex->post);
			ex->post = NULL;
		}
		if (ex->key)
		{
			free(ex->key);
			ex->key = NULL;
		}
	}
}

void	quotes_utils(char *s, t_expand_quotes *ex, int mode)
{
	if (mode == 0)
	{
		while (s && s[ex->i] && s[ex->i] != 34 && s[ex->i] != 39)
			ex->i++;
	}
	else
	{
		if (s[ex->i] == 34 || s[ex->i] == 39)
			ex->quotes = s[ex->i++];
	}
}

void	define_ex_value(t_data *data, t_expand *ex)
{
	if (ft_strcmp(ex->key, "?") == 0)
	{
		ex->value = ft_itoa(data->return_code);
		ex->free_value = 1;
	}
	else if (ft_strcmp(ex->key, "$") == 0)
		ex->value = get_env_value("MANAGERPID", data->env);
	else
		ex->value = get_env_value(ex->key, data->env);
	if (!ex->value)
		ex->value = "";
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:25:32 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/11 16:43:44 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_print_export(char *key, char *add)
{
	char	*res;
	char	*tmp;

	res = ft_strjoin("declare -x ", key);
	if (!res)
		return (NULL);
	tmp = res;
	res = ft_strjoin(res, "=\"");
	free(tmp);
	if (!res)
		return (NULL);
	tmp = res;
	res = ft_strjoin(res, add);
	free(tmp);
	if (!res)
		return (NULL);
	tmp = res;
	res = ft_strjoin(res, "\"");
	free(tmp);
	return (res);
}

void	print_export(char *value)
{
	char	*pos;
	char	*res;
	char	*key;
	char	*add;

	pos = ft_strchr(value, '=');
	if (pos == NULL)
		return ;
	key = ft_substr(value, 0, pos - value);
	if (!key)
		return ;
	add = pos + 1;
	res = build_print_export(key, add);
	free(key);
	if (!res)
		return ;
	ft_putstr_fd(res, 1);
	write(1, "\n", 1);
	free(res);
}

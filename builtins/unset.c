/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:19:08 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/25 20:41:56 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset(t_data *data, char *arg)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], arg, ft_strlen(arg)))
		{
			free(data->env[i]);
			while (data->env[i + 1])
			{
				data->env[i] = data->env[i + 1];
				i++;
			}
			data->env[i] = NULL;
		}
		else
			i++;
	}
}

static int	verif_args(char *arg)
{
	int		i;

	i = 0;
	if (!arg)
		return (0);
	if ((!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (ft_printf_fd(2, "minishell: unset: `%s': not a valid identifier\n",
				arg), 0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (ft_printf_fd(2, "minishell: unset: `%s': not a valid identifier\n",
					arg), 0);
		i++;
	}
	return (1);
}

int	parsing_unset(t_data *data, t_token **tokens)
{
	int	return_code;

	return_code = 0;
	(*tokens) = (*tokens)->next;
	if (!(*tokens))
	{
		ft_printf_fd(2, "unset: not enough arguments\n");
		return (1);
	}
	while ((*tokens) && (*tokens)->type == WORD)
	{
		if (verif_args((*tokens)->s))
			unset(data, (*tokens)->s);
		else
			return_code = 1;
		(*tokens) = (*tokens)->next;
	}
	return (return_code);
}

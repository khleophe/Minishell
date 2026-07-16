/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:07:34 by soraya            #+#    #+#             */
/*   Updated: 2026/07/16 14:52:11 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dash(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '-')
			return (-1);
		i++;
	}
	return (i);
}

int	print_export(t_data *data, int option)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (option == 1)
			ft_printf_fd(2, "declare -x %s\n", data->env[i]);
		i++;
	}
	return (i);
}

int	verif_args_export(char *arg)
{
	int		i;
	char	*eq;

	i = 0;
	if (!arg)
		return (0);
	eq = ft_strchr(arg, '=');
	if ((!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (printf("minishell: export: `%s': not a valid identifier\n",
				arg), 0);
	while (arg[i] && (&arg[i] != eq))
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (printf("minishell: export: `%s': not a valid identifier\n",
					arg), 0);
		i++;
	}
	return (1);
}

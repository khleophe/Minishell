/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:56:34 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/13 17:46:49 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//verifier avec la norme

static int	check_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || str[1] != 'n')
		return (1);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	echo_builtin(t_cmd *cmd)
{
	int	i;
	int	n;

	if (cmd->args[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	n = 0;
	while (cmd->args[i] != NULL && check_n(cmd->args[i]) == 0)
	{
		n = 1;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], 1);
		i++;
		if (cmd->args[i] != NULL)
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}

/*int	main(void)
{
	t_cmd cmd;
	char	*args[] = {"echo", "-n", NULL};
	cmd.args = args;
	cmd.redirs = NULL;
	cmd.next = NULL;
	echo_builtin(&cmd);
	return (0);
}*/

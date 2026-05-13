/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:56:55 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/20 22:07:49 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//double retour avec args(exit, 42, 2, NULL), retour return code et exit: too
//many_arguments, peut etre que 1 retour ? ou 2? jsp

int	atol_minishell(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	res;
	unsigned long long	limit;

	i = 0;
	signe = 1;
	res = 0;
	limit = (unsigned long long) LLONG_MAX + 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if ((signe == 1 && res > (unsigned long long)LLONG_MAX) || (
				signe == -1 && res > limit))
			return (EXIT_FAILURE);
	}
	if (str[i] != '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	exit_builtin(t_cmd *cmd, t_data *data)
{
	if (cmd->args[1] == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		exit(data->return_code);
	}
	if (atol_minishell(cmd->args[1]) == EXIT_FAILURE)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (2);
	}
	if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->return_code = 1;
		return (data->return_code);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit((unsigned char)ft_atol(cmd->args[1]));
	}
	return (0);
}

/*int main(void)
{
    t_data  data;
    t_cmd   cmd;

    data.env = NULL;
    data.return_code = 0;

    cmd.redirs = NULL;
    cmd.next = NULL;

    char *args[] = {"exit", "42", "2", NULL};
    cmd.args = args;

    exit_builtin(&cmd, &data);
    ft_printf("return_code = %d\n", data.return_code);
    return (0);
}*/

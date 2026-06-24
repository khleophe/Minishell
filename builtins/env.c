/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:56:52 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/13 17:42:12 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_data *path)
{
	int	i;

	i = 0;
	while (path->env[i] != NULL)
	{
		ft_putstr_fd(path->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

/*int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	t_data	path;
	path.env = env;
	path.return_code = 0;
	env_builtin(&path);
	return (0);
}*/

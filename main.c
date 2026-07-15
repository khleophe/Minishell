/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:45:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/15 13:45:25 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_flag = 0;

t_data	*get_data(void)
{
	static t_data	*data = 0;

	if (!data)
	{
		data = malloc(sizeof(*data));
		if (!data)
			exit(1);
	}
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = get_data();
	(void)argc;
	(void)argv;
	g_flag = 0;
	init(data, envp);
	read_line(&data->tokens, data);
	clean(NULL, data, 0);
	return (0);
}

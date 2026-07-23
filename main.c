/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:45:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/23 17:48:54 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_flag = 0;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:45:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/05/06 15:35:49 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_data	*data;

	(void)argc;
	(void)argv;
	token = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->env = dup_env(envp);
    data->return_code = 0;
	if (!data->env)
		return (free(data), 1);
	read_line(&token, data);
	free_tokens(token);
	// rl_clear_history
	// free
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:57:03 by nolwenng          #+#    #+#             */
/*   Updated: 2026/06/29 16:52:09 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*    Without options, unset first tries to unset a variable, and if that fails,
    tries to unset a function.
*/
//parcours env pour chercher et trouver l index
int	find_index(char *index, char **env)
{
	int	i;
	int	index_len;

	i = 0;
	index_len = ft_strlen(index);
	if (env == NULL)
		return (-1);
	while (env[i])
	{
		if (ft_strncmp(env[i], index, index_len) == 0
			&& env[i][index_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

// int	unset_builtin(t_cmd *cmd, t_data *data)
// {
// 	int	i;
// 	int	idx;

// 	i = 1;
// 	while (cmd->args[i] != NULL)
// 	{
// 		idx = find_index(cmd->args[i], data->env);
// 		if (idx != -1)
// 		{
// 			free(data->env[idx]);
// 			while (data->env[idx + 1] != NULL)
// 			{
// 				data->env[idx] = data->env[idx + 1];
// 				idx++;
// 			}
// 			data->env[idx] = NULL;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:52:41 by jdelmott          #+#    #+#             */
/*   Updated: 2026/08/06 18:54:01 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *tokens)
{
	t_token	*tmp;
	int		count;

	tmp = tokens;
	count = 0;
	if (tmp)
	{
		while (tmp && tmp->type == WORD)
		{
			count++;
			tmp = tmp->next;
		}
	}
	return (count);
}

char	**create_cmd(t_token *tokens)
{
	char	**cmd;
	int		len;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	len = count_args(tokens);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		clean("error: malloc", get_data(), 1);
	while (tmp && tmp->type == WORD && i < len)
	{
		cmd[i] = ft_strdup(tmp->s);
		if (!cmd[i])
			return (ft_freetab(cmd), clean("error: malloc", get_data(), 1),
				NULL);
		i++;
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

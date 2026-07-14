/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:41:03 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/14 15:44:20 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_builtin(t_data *data, t_token **token)
{
	if (ft_strcmp((*token)->s, "env") == 0)
		return (parsing_env(data, token));
	if (ft_strcmp((*token)->s, "unset") == 0)
		return (parsing_unset(data, token));
	if (ft_strcmp((*token)->s, "pwd") == 0)
		return (parsing_pwd(data, token));
	if (ft_strcmp((*token)->s, "export") == 0)
		return (parsing_export(data, token));
	if (ft_strcmp((*token)->s, "exit") == 0)
		return (parsing_exit(data, token));
	if (ft_strcmp((*token)->s, "echo") == 0)
		return (parsing_echo(token));
	if (ft_strcmp((*token)->s, "cd") == 0)
		return (parsing_cd(data, token));
	else
		return (0);
}

int	parsing_cmd(t_data *data, t_token *tokens)
{
	int	return_code;

	return_code = 0;
	if (apply_redirs(tokens, &return_code, data))
		return (return_code);
	while (tokens && tokens->type != PIPE)
	{
		if (is_redirs(tokens->type))
			tokens = tokens->next->next;
		if (tokens && tokens->type == WORD)
		{
			return_code = parsing_builtin(data, &tokens);
			if (tokens && tokens->type == WORD)
				return_code = exec(data, tokens);
			while (tokens && tokens->type == WORD)
				tokens = tokens->next;
		}
		else if (tokens && tokens->type != WORD)
			tokens = tokens->next;
	}
	return (return_code);
}

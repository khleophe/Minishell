/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:47:43 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/14 16:59:49 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes(char *s)
{
	int		i;
	int		j;
	char	*new;
	char	quote;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				new[j++] = s[i++];
			if (s[i] == quote)
				i++;
		}
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}

char	which_quotes(char *s, int *i)
{
	int	j;

	j = *i;
	while (s[j] && s[j] != 32 && (s[j] < 9 || s[j] > 13) && s[j] != '|'
		&& s[j] != '<' && s[j] != '>')
	{
		if (s[j] == 34 || s[j] == 39)
			return (s[j]);
		j++;
	}
	return (0);
}

void	rm_quotes_token(t_token *tokens)
{
	t_token	*tmp;
	char	*new;

	tmp = tokens;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->s)
		{
			new = remove_quotes(tmp->s);
			free(tmp->s);
			tmp->s = new;
			if (tmp->type == S_QUOTE || tmp->type == D_QUOTE)
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}

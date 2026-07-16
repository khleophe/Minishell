/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:41:37 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/16 11:23:28 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_word_quotes(char *s, char *quote)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i] && s[i] != 32 && (s[i] < 9 || s[i] > 13) && s[i] != '|'
		&& s[i] != '<' && s[i] != '>')
	{
		if (s[i] == 34 || s[i] == 39)
		{
			*quote = s[i++];
			while (s[i] && s[i] != *quote)
				i++;
			if (s[i] == *quote)
				i++;
			else
				return (NULL);
		}
		else
			i++;
	}
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		clean("error: malloc", get_data(), 1);
	ft_strlcpy(dest, s, i + 1);
	return (dest);
}

static t_token	*symbols(char *line, int *i)
{
	if (line[*i] == '|')
		return ((*i)++, new_token(PIPE, "|"));
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i) += 2, new_token(APPEND, ">>"));
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i) += 2, new_token(HEREDOC, "<<"));
	else if (line[*i] == '>')
		return ((*i)++, new_token(REDIR_OUT, ">"));
	else if (line[*i] == '<')
		return ((*i)++, new_token(REDIR_IN, "<"));
	return (NULL);
}

static t_token	*words(char *line, int *i)
{
	char	*word;
	t_token	*new;
	char	quote;

	word = extract_word_quotes(&line[*i], &quote);
	if (!word)
		return (NULL);
	if (which_quotes(line, i) == 34)
		new = new_token(D_QUOTE, word);
	else if (which_quotes(line, i) == 39)
		new = new_token(S_QUOTE, word);
	else
		new = new_token(WORD, word);
	if (!new)
		return (free(word), NULL);
	*i += ft_strlen(word);
	free(word);
	return (new);
}

t_token	*lexer(char *line)
{
	t_token	*token;
	t_token	*new;
	int		i;

	token = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == 32 || (line[i] > 9 && line[i] < 13)))
			i++;
		if (line[i])
		{
			new = symbols(line, &i);
			if (!new)
				new = words(line, &i);
			if (!new)
			{
				free_tokens(token);
				token = NULL;
				return (NULL);
			}
			add_token(&token, new);
		}
	}
	return (token);
}

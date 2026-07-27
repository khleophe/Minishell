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

static t_token	*filter_quotes(char *line, int *line_index)
{
	char	quote_char;
	char	*dest;
	t_token	*new;
	size_t	i;

	i = 1;
	quote_char = line[0];
	while (line[i] && line[i] != quote_char)
		i++;
	if (!line[i])
		return (NULL);
	dest = malloc(sizeof(char) * i);
	if (!dest)
		clean("error: malloc", get_data(), 1);
	ft_strlcpy(dest, &line[1], i);
	if (quote_char == '\'')
		new = new_token(S_QUOTE, dest);
	else
		new = new_token(D_QUOTE, dest);
	free(dest);
	*line_index += i + 1;
	return (new);
}

static char	*extract_word(char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i] && s[i] != 32 && (s[i] < 9 || s[i] > 13) && s[i] != '|'
		&& s[i] != '<' && s[i] != '>')
		i++;
	if (i == 0)
		return (NULL);
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		clean("error: malloc", get_data(), 1);
	ft_strlcpy(dest, s, i + 1);
	i++;
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

	word = extract_word(&line[*i]);
	if (word)
	{
		*i += ft_strlen(word);
		new = new_token(WORD, word);
		free(word);
		return (new);
	}
	return (filter_quotes(&line[*i], i));
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

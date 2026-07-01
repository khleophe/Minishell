/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:41:37 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/15 15:27:29 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_word_quotes(char *s)
{
	int		i;
	char	*dest;
	char	quote;

	i = 0;
	while (s[i] && s[i] != 32 && (s[i] < 9 || s[i] > 13) && s[i] != '|' && s[i] != '<' && s[i] != '>')
	{
		if (s[i] == 34 || s[i] == 39)
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				i++;
			else
				return (NULL);
		}
		else
			i++;
	}
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, i + 1);
	return (dest);
}

static t_token *symbols(char *line, int *i)
{
	if (line[*i] == '|')
		return((*i)++, new_token(PIPE, "|"));
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i)+= 2, new_token(APPEND, ">>"));
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i) += 2, new_token(HEREDOC, "<<"));
	else if (line[*i] == '>')
		return ((*i)++, new_token(REDIR_OUT, ">"));
	else if (line[*i] == '<')
		return ((*i)++, new_token(REDIR_IN, "<"));
	return (NULL);
}

char	which_quotes(char *s, int *i)
{
	int	j;

	j = *i;
	while (s[j] && s[j] != 32 && (s[j] < 9 || s[j] > 13) && s[j] != '|' && s[j] != '<' && s[j] != '>')
	{
		if (s[j] == 34 || s[j] == 39)
			return (s[j]);
		j++;
	}
	return (0);
}
static t_token *words(char *line, int *i)
{
	char	*word;
	t_token	*new;
	
	word = extract_word_quotes(&line[*i]);
	if (!word)
		return (NULL);
	if (which_quotes(line, i) == 34)
		new = new_token(D_QUOTE, word);
	else if (which_quotes(line, i) == 39)
		new = new_token(S_QUOTE, word);
	else
		new = new_token(WORD, word);
	if (!new)
		return (free(word),NULL);
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

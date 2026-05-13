/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:59:10 by soraya            #+#    #+#             */
/*   Updated: 2026/05/13 17:03:50 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_expand(char *s, int i)
{
	int	j;
	int	len;

	len = 0;
	if (s[i] == '$' && s[i + 1])
	{
		j = i + 1;
		while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
			j++;
		len = j - i;
	}
	return (len);
}

static char	*new_expand(char *s, int i, int len, t_data *data)
{
	char	*pre_var;
	char	*key;
	char	*post_var;
	char	*value;
	char	*tmp;
	char	*result;

	pre_var = ft_substr(s, 0, i);
	key = ft_substr(s, i + 1, len - 1);
	post_var = ft_strdup(s + i + len);
	if (!pre_var || !key || !post_var)
	{
		free(pre_var);
		free(key);
		free(post_var);
		return (NULL);
	}
	value = get_env_value(key, data->env);
	if (!value)
		value = "";
	free(key);
	tmp = ft_strjoin(pre_var, value);
	result = ft_strjoin(tmp, post_var);
	return (free(pre_var), free(post_var), free(tmp), result);
}

char	*expand_str(char *s, t_data *data)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	while (s && s[i])
	{
		len = get_new_expand(s, i);
		if (s[i] == '$' && len > 0)
		{
			
			new = new_expand(s, i, len, data);
			free(s);
			s = new;
			//i = 0;
		}
		else
			i++;
	}
	return (s);
}

static char	*expand_str_quotes(char *s, t_data *data)
{
	char	*new;
	int		i;
	int		len;
	char	quotes;

	i = 0;
	quotes = -1;
	while (s && s[i] && s[i] != 34 && s[i] != 39)
		i++;
	while (s && s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			quotes = s[i];
			i++;
		}
		while (s && s[i] && s[i] != quotes)
		{
			if (quotes == 34 || quotes == -1)
			{
				len = get_new_expand(s, i);
				if (s[i] == '$' && len > 0)
				{
					new = new_expand(s, i, len, data);
					free(s);
					s = new;
				}
			}
			i++;
		}
		i++;
	}
	return (s);
}

void	expand_all_tokens(t_token *token, t_data *data)
{
	t_token	*tmp;

	if (!token)
		return ;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == D_QUOTE || tmp->type == S_QUOTE)
			tmp->s = expand_str_quotes(tmp->s, data);
		else
			tmp->s = expand_str(tmp->s, data);
		tmp = tmp->next;
	}
	rm_quotes_token(token);
}

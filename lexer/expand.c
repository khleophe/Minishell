/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:59:10 by soraya            #+#    #+#             */
/*   Updated: 2026/07/14 18:09:27 by sdabbas          ###   ########.fr       */
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
	t_expand	ex;

	ex.pre = ft_substr(s, 0, i);
	utils_expand(s, i, len, &ex);
	if (ex.post == NULL || ex.key == NULL)
		clean(NULL, data, 1);
	if (!ex.pre || !ex.key || !ex.post)
		return (free(ex.pre), free(ex.key), free(ex.post), NULL);
	if (ft_strcmp(ex.key, "?") == 0)
		ex.value = ft_itoa(data->return_code);
	else if (ft_strcmp(ex.key, "$") == 0)
		ex.value = get_env_value("MANAGERPID", data->env);
	else
		ex.value = get_env_value(ex.key, data->env);
	if (!ex.value)
		ex.value = "";
	ex.tmp = ft_strjoin(ex.pre, ex.value);
	ex.res = ft_strjoin(ex.tmp, ex.post);
	return (free(ex.pre), free(ex.post), free(ex.tmp), free(ex.key), ex.res);
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
		}
		else
			i++;
	}
	return (s);
}

static char	*expand_str_quotes(char *s, t_data *data)
{
	t_expand_quotes	ex;

	ex.i = 0;
	ex.quotes = -1;
	quotes_utils(s, &ex, 0);
	while (s && s[ex.i])
	{
		quotes_utils(s, &ex, 1);
		while (s && s[ex.i] && s[ex.i] != ex.quotes)
		{
			if (ex.quotes == 34 || ex.quotes == -1)
			{
				ex.len = get_new_expand(s, ex.i);
				if (s[ex.i] == '$' && ex.len > 0)
				{
					ex.new = new_expand(s, ex.i, ex.len, data);
					free(s);
					s = ex.new;
				}
			}
			ex.i++;
		}
		ex.i++;
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

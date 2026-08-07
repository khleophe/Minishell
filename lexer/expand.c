/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:59:10 by soraya            #+#    #+#             */
/*   Updated: 2026/08/07 04:10:53 by jdelmott         ###   ########.fr       */
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

static void	free_ex(t_expand *ex)
{
	if (ex->post)
		free(ex->post);
	if (ex->tmp)
		free(ex->tmp);
	if (ex->key)
		free(ex->key);
	if (ex->pre)
		free(ex->pre);
	if (ex->free_value == 1)
		free(ex->value);
}

static char	*new_expand(char *s, int i, int len, t_data *data)
{
	t_expand	ex;

	ex.free_value = 0;
	ex.pre = ft_substr(s, 0, i);
	utils_expand(s, i, len, &ex);
	if (ex.post == NULL || ex.key == NULL)
		clean(NULL, data, 1);
	if (!ex.pre || !ex.key || !ex.post)
		return (free_ex(&ex), clean("error: malloc", data, 1), NULL);
	if (ft_strcmp(ex.key, "?") == 0)
	{
		ex.value = ft_itoa(data->return_code);
		ex.free_value = 1;
	}
	else
		ex.value = get_env_value(ex.key, data->env);
	if (!ex.value)
		ex.value = "";
	ex.tmp = ft_strjoin(ex.pre, ex.value);
	if (!ex.tmp)
		return (free_ex(&ex), clean("", data, 1), NULL);
	ex.res = ft_strjoin(ex.tmp, ex.post);
	if (!ex.res)
		return (free_ex(&ex), clean("error: malloc", data, 1), NULL);
	return (free_ex(&ex), ex.res);
}

char	*expand_str_quotes(char *s, t_data *data)
{
	t_expand_quotes	ex;

	ex.i = 0;
	while (s && s[ex.i])
	{
		ex.quotes = -1;
		while (s && s[ex.i] && s[ex.i] != ex.quotes)
		{
			quotes_utils(s, &ex, 1);
			if (ex.quotes == 34 || ex.quotes == -1)
			{
				ex.len = get_new_expand(s, ex.i);
				if (s && s[ex.i] && s[ex.i] == '$' && ex.len > 0)
				{
					ex.new = new_expand(s, ex.i, ex.len, data);
					free(s);
					s = ex.new;
				}
			}
			add_ex_i(s, &ex);
		}
		add_ex_i(s, &ex);
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
		tmp->is = 0;
		if (tmp->s)
			tmp->s = expand_str_quotes(tmp->s, data);
		tmp->is = 1;
		tmp = tmp->next;
	}
	rm_quotes_token(token);
}

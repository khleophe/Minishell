/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:59:10 by soraya            #+#    #+#             */
/*   Updated: 2026/08/04 17:14:54 by sdabbas          ###   ########.fr       */
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
	free(ex->post);
	free(ex->tmp);
	free(ex->key);
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
		return (free(ex.pre), free(ex.key), free(ex.post),
			clean("error: malloc", data, 1), NULL);
	if (ft_strcmp(ex.key, "?") == 0)
		ex.value = ft_itoa(data->return_code);
	else
		ex.value = get_env_value(ex.key, data->env);
	if (!ex.value)
		ex.value = "";
	ex.tmp = ft_strjoin(ex.pre, ex.value);
	if (ex.free_value == 1)
		free(ex.value);
	if (!ex.tmp)
		return (free(ex.tmp), free(ex.key), clean("", data, 1), NULL);
	ex.res = ft_strjoin(ex.tmp, ex.post);
	if (!ex.res)
		return (free_ex(&ex), clean("error: malloc", data, 1), NULL);
	return (free(ex.pre), free(ex.post), free(ex.tmp), free(ex.key), ex.res);
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
				if (s[ex.i] == '$' && ex.len > 0)
				{
					ex.new = new_expand(s, ex.i, ex.len, data);
					free(s);
					s = ex.new;
				}
			}
			ex.i++;
		}
		if (s[ex.i])
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
		tmp->s = expand_str_quotes(tmp->s, data);
		tmp = tmp->next;
	}
	rm_quotes_token(token);
}

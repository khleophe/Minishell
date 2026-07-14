/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:53:20 by soraya            #+#    #+#             */
/*   Updated: 2026/07/14 15:36:29 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitdup(char **str)
{
	int		i;
	char	**cpy;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	cpy = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (str[i])
	{
		cpy[i] = ft_strdup(str[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

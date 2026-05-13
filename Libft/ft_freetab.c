/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:25:50 by sdabbas           #+#    #+#             */
/*   Updated: 2026/04/20 15:52:46 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_freetab(char **dest)
{
	int	i;

	if (!dest)
		return (NULL);
	i = 0;
	while (dest[i])
	{
		if (dest[i])
			free(dest[i]);
		i++;
	}
	free(dest);
	return (NULL);
}

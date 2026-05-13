/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:33:57 by sdabbas           #+#    #+#             */
/*   Updated: 2025/11/14 17:45:58 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *str)
{
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dest)
		return (0);
	ft_strcpy(dest, str);
	return (dest);
}

/*int	main(int argc, char *argv[])
{
	(void)argc;
	free(ft_strdup(argv[1]));
	return (0);
}*/

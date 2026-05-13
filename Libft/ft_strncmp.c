/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:56:45 by sdabbas           #+#    #+#             */
/*   Updated: 2025/11/17 15:08:15 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < n - 1 && str1[i])
	{
		if (!ft_isascii(str1[i]) || !ft_isascii(str2[i]))
			return (1);
		i++;
	}
	return ((int)(str1[i] - str2[i]));
}

/*int	main(void)
{
	printf("%d", ft_strncmp("billar", "billard", 7));
	return (0);
}*/

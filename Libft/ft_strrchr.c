/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:38:50 by sdabbas           #+#    #+#             */
/*   Updated: 2026/01/15 18:18:07 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*last;
	char	letter;

	letter = (char)c;
	last = NULL;
	while (*str)
	{
		if (*str == letter)
			last = (char *)str;
		str++;
	}
	if (last != NULL)
		return (last);
	if (letter == '\0')
		return ((char *)str);
	return (NULL);
}

/*int	main(void)
{
	printf("%s", ft_strrchr("anatole", 'I'));
	return (0);
}*/

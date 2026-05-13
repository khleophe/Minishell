/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:28:53 by sdabbas           #+#    #+#             */
/*   Updated: 2025/11/17 15:15:05 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	letter;

	i = 0;
	letter = (char)c;
	while (str[i])
	{
		if (str[i] == letter)
			return ((char *)&str[i]);
		i++;
	}
	if (letter == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

/*int	main(void)
{
	printf("%s", ft_strchr("jolen", 'a'));
	return (0);
}*/

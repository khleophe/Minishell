/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:10:49 by sdabbas           #+#    #+#             */
/*   Updated: 2025/11/17 15:54:24 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	size_t			i;

	i = 0;
	string = (unsigned char *)s;
	while (i < n)
	{
		if (string[i] == (unsigned char)c)
			return (string + i);
		i++;
	}
	return (NULL);
}

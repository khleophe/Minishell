/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:50:55 by sdabbas           #+#    #+#             */
/*   Updated: 2025/11/17 10:06:32 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*string;
	size_t			i;
	unsigned char	value;

	string = (unsigned char *)s;
	value = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		string[i] = value;
		i++;
	}
	return (s);
}

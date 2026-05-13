/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:27 by sdabbas           #+#    #+#             */
/*   Updated: 2025/11/19 13:33:12 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*dest;
	int long	n1;
	int long	s1;

	n1 = (int long)nmemb;
	s1 = (int long)size;
	if ((nmemb * size > SIZE_MAX) || (n1 < 0 && s1 < 0))
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, (nmemb * size));
	return (dest);
}

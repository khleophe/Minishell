/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:26:54 by sdabbas           #+#    #+#             */
/*   Updated: 2025/11/17 14:54:06 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;
	size_t	final;

	i = 0;
	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (n == 0)
		return (len_src);
	if (n > len_dest)
		final = len_dest + len_src;
	else
		final = len_src + n;
	while (src[i] && len_dest + i < n - 1)
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (final);
}

/*int	main(int argc, char *argv[])
{
	(void)argc;
	printf("%zu\n", ft_strlcat(argv[1], argv[2], 5));
	printf("%zu\n", strlcat(argv[1], argv[2], 5));
}*/

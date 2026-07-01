/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:39:49 by jdelmott          #+#    #+#             */
/*   Updated: 2026/06/25 14:49:39 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(unsigned int i, char *base, int fd)
{
	static int		k;
	unsigned int	len_base;
	size_t			index;

	k = 0;
	index = 0;
	len_base = (unsigned int)ft_strlen(base);
	if (i >= len_base)
		ft_putnbr_base_fd(i / len_base, base, fd);
	index = (i % len_base);
	k++;
	if (ft_putchar_fd(base[index], fd) == -1)
		return (-1);
	return (k);
}

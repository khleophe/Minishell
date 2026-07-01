/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_p_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:37:05 by jdelmott          #+#    #+#             */
/*   Updated: 2026/06/25 14:49:54 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print(unsigned long i, int fd)
{
	char		*base;
	static int	k;
	int			j;

	k = 0;
	base = "0123456789abcdef";
	if (i > 15)
		ft_print(i / 16, fd);
	j = ft_putchar_fd(base[i % 16], fd);
	if (j == -1)
		return (-1);
	k += j;
	return (k);
}

int	ft_putnbr_p_fd(unsigned long s, int fd)
{
	if (s == 0)
		return (ft_putstr_fd("(nil)", fd));
	ft_putstr_fd("0x", fd);
	return (ft_print(s, fd) + 2);
}

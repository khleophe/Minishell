/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:03:22 by jdelmott          #+#    #+#             */
/*   Updated: 2026/06/25 14:50:01 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_u_fd(unsigned int i, int fd)
{
	static int	k;
	int			j;

	k = 0;
	if (i >= 10)
		ft_putnbr_u_fd(i / 10, fd);
	j = ft_putchar_fd((i % 10) + '0', fd);
	if (j == -1)
		return (-1);
	k += j;
	return (k);
}

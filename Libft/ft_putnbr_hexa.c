/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:06:49 by sdabbas           #+#    #+#             */
/*   Updated: 2026/03/09 13:03:24 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hexa(int n)
{
	char		*base;
	long int	nb;
	int			i;

	base = "0123456789abcdef";
	nb = (long int)n;
	i = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = nb * -1;
	}
	if (nb >= 16)
		ft_putnbr(nb / 16);
	i = (nb % 16);
	ft_putchar(base[i]);
}

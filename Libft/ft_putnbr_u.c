/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:51:47 by sdabbas           #+#    #+#             */
/*   Updated: 2026/03/09 13:10:40 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_u(unsigned int n)
{
	static int	count;

	count = 0;
	if (n >= 10)
		ft_putnbr_u(n / 10);
	if ((ft_putchar(n % 10 + '0') == -1))
		return (-1);
	count++;
	return (count);
}

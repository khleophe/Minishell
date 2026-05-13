/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:48:24 by sdabbas           #+#    #+#             */
/*   Updated: 2026/03/05 14:22:45 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(int n)
{
	static int	count;
	int			neg;

	neg = 0;
	count = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		n = n * -1;
		neg++;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	if (ft_putchar(n % 10 + '0') == -1)
		return (-1);
	if (neg != 0)
		count++;
	count++;
	return (count);
}

int	ft_putnbr_base(unsigned int n, char *base)
{
	unsigned int	len;
	static int		count;

	count = 0;
	len = (unsigned int)ft_strlen(base);
	if (n >= len)
		ft_putnbr_base(n / len, base);
	count++;
	if (ft_putchar(base[n % len]) == -1)
		return (-1);
	return (count);
}

static int	ft_putnbrbis(unsigned long n)
{
	char		*base;
	static int	count;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		ft_putnbrbis(n / 16);
	count++;
	if (ft_putchar(base[n % 16]) == -1)
		return (-1);
	return (count);
}

int	ft_putnbr_base_p(unsigned long n)
{
	if (n == 0)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (ft_putnbrbis(n) + 2);
}

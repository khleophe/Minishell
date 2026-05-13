/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:28:15 by sdabbas           #+#    #+#             */
/*   Updated: 2026/03/05 14:31:15 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_type(const char *str, va_list *lst, int *i)
{
	*i = (*i + 1);
	if (*(str + 1) == 'i' || *(str + 1) == 'd')
		return (ft_putnbr(va_arg(*lst, int)));
	else if (*(str + 1) == 'u')
		return (ft_putnbr_u(va_arg(*lst, int)));
	else if (*(str + 1) == 's')
		return (ft_putstr(va_arg(*lst, char *)));
	else if (*(str + 1) == 'c')
		return (ft_putchar(va_arg(*lst, int)));
	else if (*(str + 1) == 'p')
		return (ft_putnbr_base_p(va_arg(*lst, unsigned long)));
	else if (*(str + 1) == 'x')
		return (ft_putnbr_base(va_arg(*lst, unsigned int), "0123456789abcdef"));
	else if (*(str + 1) == 'X')
		return (ft_putnbr_base(va_arg(*lst, unsigned int), "0123456789ABCDEF"));
	else if (*(str + 1) == '%')
		return (ft_putchar('%'));
	else if (*(str + 1) == '\0')
		*i = *i - 1;
	else
		return (ft_putchar('%') + ft_putchar(*(str + 1)));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		i;
	int		count;
	int		temp;

	va_start(list, str);
	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] != '%' && str[i])
			temp = ft_putchar(str[i]);
		if (str[i] == '%')
			temp = ft_type(str + i, &list, &i);
		if (temp >= 0)
			count += temp;
		else
			count = temp;
		i++;
	}
	va_end(list);
	return (count);
}

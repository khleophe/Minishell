/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:01:41 by jdelmott          #+#    #+#             */
/*   Updated: 2026/06/25 14:49:26 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verif(const char *str, va_list *lst, int *i, int fd)
{
	*i += 1;
	if (*(str + 1) == 'c')
		return (ft_putchar_fd(va_arg(*lst, int), fd));
	else if (*(str + 1) == 's')
		return (ft_putstr_fd(va_arg(*lst, char *), fd));
	else if (*(str + 1) == 'p')
		return (ft_putnbr_p_fd(va_arg(*lst, unsigned long), fd));
	else if (*(str + 1) == 'x')
		return (ft_putnbr_base_fd(va_arg(*lst, unsigned int),
				"0123456789abcdef", fd));
	else if (*(str + 1) == 'i' || *(str + 1) == 'd')
		return (ft_putnbr_fd(va_arg(*lst, int), fd));
	else if (*(str + 1) == 'u')
		return (ft_putnbr_u_fd(va_arg(*lst, int), fd));
	else if (*(str + 1) == 'X')
		return (ft_putnbr_base_fd(va_arg(*lst, unsigned int),
				"0123456789ABCDEF", fd));
	else if (*(str + 1) == '%')
		return (ft_putchar_fd('%', fd));
	else if (*(str + 1))
		return (ft_putchar_fd(*str, fd) + ft_putchar_fd(*(str + 1), fd));
	else
		*i -= 1;
	return (-1);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	lst;
	int		i;
	int		len;
	int		temp;

	temp = 0;
	len = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%')
			temp = verif(str + i, &lst, &i, fd);
		else
			temp = ft_putchar_fd(str[i], fd);
		if (temp >= 0)
			len += temp;
		else
			len = temp;
		i++;
	}
	va_end(lst);
	return (len);
}

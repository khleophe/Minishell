/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:10:22 by jdelmott          #+#    #+#             */
/*   Updated: 2026/06/25 14:50:06 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr_fd("(null)", fd));
	while (str[i])
	{
		if (ft_putchar_fd(str[i], fd) == -1)
			return (-1);
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:55:30 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/18 13:31:32 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	res;
	unsigned long long	limit;

	i = 0;
	signe = 1;
	res = 0;
	limit = (unsigned long long) LLONG_MAX + 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if ((signe == 1 && res > (unsigned long long)LLONG_MAX) || (
				signe == -1 && res > limit))
			return (EXIT_FAILURE);
	}
	if (str[i] != '\0')
		return (EXIT_FAILURE);
	return ((long)res * signe);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:16:10 by sdabbas           #+#    #+#             */
/*   Updated: 2026/03/05 14:23:15 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (str == 0)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		if (write(1, &str[i], 1) == -1)
			return (-1);
		i++;
		count++;
	}
	return (count);
}

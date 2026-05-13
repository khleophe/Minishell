/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:48:49 by sdabbas           #+#    #+#             */
/*   Updated: 2025/11/18 10:04:04 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_cpy(int start, int end, const char *s1, char *trimmed)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		trimmed[i] = s1[start];
		i++;
		start++;
	}
	trimmed[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trimmed;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1 && ft_strchr(set, s1[start]))
		start++;
	while (s1 && ft_strchr(set, s1[end]))
		end--;
	if (end - start < 0)
	{
		trimmed = malloc(1);
		if (!trimmed)
			return (NULL);
		trimmed[0] = '\0';
		return (trimmed);
	}
	trimmed = malloc(sizeof (char) * (end - start + 2));
	if (!trimmed)
		return (NULL);
	ft_cpy(start, end, s1, trimmed);
	return (trimmed);
}
/*int	main(void)
{
	printf("%s", ft_strtrim("123un312", "123"));
	return (0);
}*/

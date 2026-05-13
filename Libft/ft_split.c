/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:33:00 by sdabbas           #+#    #+#             */
/*   Updated: 2026/03/25 04:56:47 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s1, char a)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i])
	{
		if ((s1[i] != '\0' && s1[i] != a)
			&& (s1[i + 1] == '\0' || s1[i + 1] == a))
			count++;
		i++;
	}
	return (count);
}

static char	**ft_freetab_split(char **dest, int i)
{
	while (i >= 0)
	{
		free(dest[i]);
		i--;
	}
	free(dest);
	return (NULL);
}

static void	fill(char const *s, char c, char *dest)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (s[i] != c && s[i])
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}

static char	**tab(char const *s, char c, char **dest)
{
	int	i;
	int	size;
	int	arg;

	arg = 0;
	i = 0;
	dest[ft_countwords(s, c)] = NULL;
	while (arg < ft_countwords(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		size = 0;
		while (s[i + size] != c && s[i + size])
			size++;
		dest[arg] = malloc(sizeof (char) * (size + 1));
		if (!dest[arg])
			return (ft_freetab_split(dest, arg));
		fill(&s[i], c, dest[arg]);
		arg++;
		i = i + size;
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	dest = malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!dest)
		return (NULL);
	if (!s[0])
	{
		dest[0] = 0;
		return (dest);
	}
	return (tab(s, c, dest));
}

/*int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char	**tabstr = ft_split(argv[1], argv[2][0]);
	int	i;

	i = 0;
	while (tabstr[i])
	{
		printf("%s\n", tabstr[i]);
		i++;
	}
}*/

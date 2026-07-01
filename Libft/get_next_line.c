/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:48:54 by sdabbas           #+#    #+#             */
/*   Updated: 2026/03/05 14:23:00 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 1000

char	*join_tab(char *mid_tab, char *temp)
{
	char	*mid_tab_temp;

	mid_tab_temp = ft_strjoin(mid_tab, temp);
	free(mid_tab);
	return (mid_tab_temp);
}

static char	*read_fd(int fd, char *mid_tab)
{
	char	*temp;
	int		read_return;

	read_return = 1;
	if (mid_tab == NULL)
		mid_tab = ft_calloc(1, 1);
	temp = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	while (!ft_strchr(temp, '\n') && read_return > 0)
	{
		read_return = read(fd, temp, BUFFER_SIZE);
		if (read_return == -1)
		{
			free(temp);
			free(mid_tab);
			return (NULL);
		}
		temp[read_return] = '\0';
		mid_tab = join_tab(mid_tab, temp);
	}
	free(temp);
	return (mid_tab);
}

static char	*return_line(char *mid_tab)
{
	char	*line;
	int		i;

	i = 0;
	if (mid_tab[i] == '\0')
		return (NULL);
	while (mid_tab[i] != '\n' && mid_tab[i])
		i++;
	line = ft_calloc(sizeof (char), i + 2);
	i = 0;
	while (mid_tab[i] != '\n' && mid_tab[i])
	{
		line[i] = mid_tab[i];
		i++;
	}
	if (mid_tab[i] == '\n' && mid_tab[i])
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*next_line(char	*mid_tab)
{
	int		i;
	int		j;
	char	*next_temp;

	i = 0;
	while (mid_tab[i] != '\n' && mid_tab[i])
		i++;
	if (mid_tab[i] == '\0')
	{
		free(mid_tab);
		return (NULL);
	}
	next_temp = ft_calloc(sizeof(char), ft_strlen(&mid_tab[i]) + 1);
	i++;
	j = 0;
	while (mid_tab[i])
		next_temp[j++] = mid_tab[i++];
	next_temp[j] = '\0';
	free(mid_tab);
	return (next_temp);
}

char	*get_next_line(int fd)
{
	char		*retour;
	static char	*queen_tab[1024];

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0))
	{
		free(queen_tab[fd]);
		queen_tab[fd] = NULL;
		return (NULL);
	}
	queen_tab[fd] = read_fd(fd, queen_tab[fd]);
	if (queen_tab[fd] == NULL)
	{
		free(queen_tab[fd]);
		return (NULL);
	}
	retour = return_line(queen_tab[fd]);
	queen_tab[fd] = next_line(queen_tab[fd]);
	return (retour);
}

/*int	main(void)
{
	int	fd;
	char	*temp;

	fd = open("v.txt", O_RDONLY);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s", temp);
	free(temp);
	return (0);
}*/

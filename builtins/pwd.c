/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolwenng <nolwenng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:57:01 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/11 13:49:22 by nolwenng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	free(buf);
	return (0);
}

/*int	main(void)
{
	pwd_builtin();
	return (0);
}*/

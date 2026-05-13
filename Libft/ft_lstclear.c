/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:22:26 by sdabbas           #+#    #+#             */
/*   Updated: 2026/03/05 13:56:04 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;

	if (!lst)
		return ;
	while (*lst)
	{
		list = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = list;
	}
	*lst = NULL;
}

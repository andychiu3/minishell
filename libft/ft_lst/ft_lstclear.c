/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:52:15 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/22 11:02:33 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;

	if (lst && *lst && del)
	{
		while (*lst)
		{
			cur = *lst;
			*lst = (*lst)->next;
			ft_lstdelone(cur, del);
		}
		*lst = NULL;
	}
}

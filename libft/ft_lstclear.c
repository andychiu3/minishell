/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:52:15 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/06/17 15:58:27 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;

	if (lst && del)
	{
		while (*lst)
		{
			cur = *lst;
			*lst = (*lst)->next;
			ft_lstdelone(cur, del);
		}
	}
}

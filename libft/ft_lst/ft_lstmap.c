/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:46:46 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/05/20 12:50:27 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*tmp;

	map = 0;
	tmp = lst;
	if (lst && f && del)
	{
		while (lst)
		{
			tmp = ft_lstnew(f(lst->content));
			if (!tmp)
			{
				ft_lstclear(&tmp, del);
				return (0);
			}
			ft_lstadd_back(&map, tmp);
			lst = lst->next;
		}
	}
	return (map);
}

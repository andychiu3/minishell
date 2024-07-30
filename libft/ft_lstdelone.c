/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:13:49 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/05/19 20:11:07 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		(*del)(lst->content);
		free(lst);
	}
}

// int	main(void)
// {
// 	int		f = 1;
// 	int		s = 2;
// 	int		t = 3;
// 	t_list	*first = ft_lstnew(&f);
// 	t_list	*second = ft_lstnew(&s);
// 	t_list	*third = ft_lstnew(&t);
// 	t_list	*cur;

// 	first->next = second;
// 	second->next = third;

// 	cur = first;
// 	ft_lstdelone(cur, &free);
// 	while (cur)
// 	{
// 		printf("%d ", *((int *)cur->content));
// 		cur = cur->next;
// 	}
// 	printf("\n");
// 	free(first);
// 	free(second);
// 	free(third);

// 	return (0);
// }

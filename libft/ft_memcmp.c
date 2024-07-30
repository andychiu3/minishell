/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:45:54 by achiu             #+#    #+#             */
/*   Updated: 2024/03/17 08:02:46 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

// below could not handle the \0\0 situation properly.
// while (i < n && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]
// 		&& ((unsigned char *)s1)[i] && ((unsigned char *)s2)[i])
// 		i++;
// 	if (i == n)
// 		return (0);
// 	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
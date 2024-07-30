/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:02:56 by achiu             #+#    #+#             */
/*   Updated: 2024/03/15 11:44:20 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst || src)
	{
		if ((char *)dst > (char *)src)
		{
			i = len;
			while (i--)
				((char *)dst)[i] = ((char *)src)[i];
		}
		else
		{
			i = 0;
			while (i < len)
			{
				((char *)dst)[i] = ((char *)src)[i];
				i++;
			}
		}
	}
	return (dst);
}

// function needs crushing if either dst or src is NULL
// function works if both dst and src are NULL
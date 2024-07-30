/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:47:35 by achiu             #+#    #+#             */
/*   Updated: 2024/03/14 17:51:21 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	i;

	dst = (ft_strdup(s));
	if (!dst)
		return (0);
	i = 0;
	while (dst[i])
	{
		dst[i] = (*f)(i, dst[i]);
		i++;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:12:46 by achiu             #+#    #+#             */
/*   Updated: 2024/03/15 00:14:16 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
		j++;
	if (i > dstsize || dstsize == 0)
		return (j + dstsize);
	k = 0;
	while (src[k] && --dstsize && dstsize > i)
	{
		dest[i + k] = src[k];
		k++;
	}
	dest[i + k] = 0;
	return (i + j);
}

// line 27 i > dstsize in def was using i >= dstsize - 1...
// line 27 (dstsize == 0) in def
// below doesn't work tho don't know why yet
// size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
// {
// 	size_t	i;

// 	if (ft_strlen(dest) >= (int)dstsize - 1 || dstsize == 0)
// 		return (ft_strlen(src) + dstsize);
// 	i = 0;
// 	while (src[i] && --dstsize && (int)dstsize - 1 > ft_strlen(dest))
// 	{
// 		dest[ft_strlen(dest) + i] = src[i];
// 		i++;
// 	}
// 	dest[ft_strlen(dest) + i] = 0;
// 	return (ft_strlen(dest));
// }

// int	main()
// {
// 	char	*src = "lorem ipsum dolor sit amet";
// 	char	dest[2] = "r";

// 	printf("\n%zu\n", ft_strlcat(dest, src, 2));
// 	printf("%s\n", dest);
// 	printf("real: %lu\n", strlcat(dest, src, 2));
// 	printf("%s\n", dest);
// }
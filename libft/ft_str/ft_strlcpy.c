/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <achiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:12:52 by achiu             #+#    #+#             */
/*   Updated: 2024/03/13 18:31:19 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dest, const char *src, int size)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	if (!size)
		return (i);
	while (*src && --size)
		*dest++ = *src++;
	*dest = 0;
	return (i);
}

// int	main()
// {
// 	char	*src = "lorem ipsum dolor sit amet";
// 	char	dest[10] = "";

// 	printf("\n%d\n", ft_strlcpy(dest, src, 0));
// 	printf("%s\n", dest);
	// printf("real: %lu\n", strlcpy(dest, src, 2));
	// printf("%s\n", dest);
// }

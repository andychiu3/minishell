/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:12:59 by achiu             #+#    #+#             */
/*   Updated: 2024/03/14 13:46:06 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& (unsigned char)s1[i] && (unsigned char)s2[i]
		&& i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// 1. should be s1 - s2 according to def.
// 2. was using n-- in while 
// but ft_strncmp("abcandy", "abcjlkji", 3) will be wrong
// int	main()
// {
// 	char	*s1 = "";
// 	char	*s2 = "world ";
// 	int		n = 6;
// 	printf("real: %d\n", strncmp(s1, s2, n));
// 	printf("%d\n", ft_strncmp(s1, s2, n));
// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:14:11 by achiu             #+#    #+#             */
/*   Updated: 2024/03/17 08:52:01 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

// int	main(void)
// {
// 	char *s = "teste";
// 	printf("%p\n%p\n", s, ft_strchr(s, 'e'));
// }
// int	main(void)
// {
// 	char	*s1 = "tht";
// 	char	*set = "t";
// 	int		start = 0;
// 
// 	while (ft_strchr(set, s1[start]))
// 	{
// 		start++;
// 		printf("%p\n", ft_strchr(set, s1[start]));
// 	}
// 	return (0);
// }
//didn't consider the \0
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <achiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:59:36 by achiu             #+#    #+#             */
/*   Updated: 2024/03/18 10:58:09 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (haystack[i + j] == 0 && needle[j] == 0)
				return ((char *)&haystack[i]);
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}

// would have to use *needle instead of needle[i]
// int	main(void) 
// {
//     char str[] = "oh no not the empty string !";
// 	int	len = 0;
// 	char	needle[] = "";
//     char *result = ft_strnstr(str, needle, len);

//     if (result != NULL) {
//         printf("Substring found at index: %ld\n", result - str);
//     } else {
//         printf("Substring not found\n");
//     }
//     return 0;
// }

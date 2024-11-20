/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:28:36 by achiu             #+#    #+#             */
/*   Updated: 2024/03/17 08:54:16 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	while (i && s[i] != (char)c)
		i--;
	if (s[i] != (char)c)
		return (0);
	return ((char *)&s[i]);
}

// form c to char to consider the situation of amount is not within ASCII
// ft_strrchr(0x1026e6e20: "teste", 1125: 'e')
// int main(void) 
// {
//     char *src = "bonjourno";
//     char *d2 = ft_strrchr(src, 'o');
//     printf("ft_strrchr result: %s\n", d2);

//     return 0;
// }
//your strrchr crash because it read too many bytes or attempt to write on s

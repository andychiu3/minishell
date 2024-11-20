/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:09:35 by achiu             #+#    #+#             */
/*   Updated: 2024/03/14 11:01:00 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end && ft_strchr(set, s1[end - 1]) && end - start > 0)
		end--;
	return (ft_substr(s1, start, (end - start)));
}

// int	main(void)
// {
// 	char	*s1 = "          ";
// 	char	*set = " ";
// 	char	*result = ft_strtrim(s1, set);

// 	if (result)
// 		printf("%s\n", result);
// 	else
// 		printf("Error occurred during trimming\n");
// 	return (0);
// }

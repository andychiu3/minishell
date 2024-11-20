/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:43:00 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/10 11:43:02 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnbr(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '+' || str[i] == '-')
			i++;
		if (str[i] == '\0')
			return (0);
		while (str[i] && str[i] != ' ')
			if (!ft_isdigit(str[i++]))
				return (0);
		while (str[i] == ' ')
			i++;
		return ((size_t)i == ft_strlen(str));
	}
	return (0);
}

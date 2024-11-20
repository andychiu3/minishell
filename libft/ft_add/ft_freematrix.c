/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:27:14 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/03 08:28:08 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// make the ptr NULL after free in case errors happen
void	ft_freematrix(char ***matrix)
{
	size_t	y;

	if (!matrix || !*matrix)
		return ;
	y = 0;
	while ((*matrix)[y])
	{
		free ((*matrix)[y]);
		(*matrix)[y++] = NULL;
	}
	free (*matrix);
	*matrix = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str_with_nextline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:39:36 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/11 09:57:35 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// no freeing for add but original total
void	add_str_with_nextline(char **total, char *add)
{
	char	*tmp;

	if (add && *add)
	{
		if (!*total)
			*total = ft_strjoin(add, "\n");
		else
		{
			tmp = ft_strjoin(*total, add);
			free(*total);
			*total = ft_strjoin(tmp, "\n");
			free(tmp);
		}
	}
}

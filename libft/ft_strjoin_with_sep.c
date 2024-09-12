/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <achiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:43:20 by achiu             #+#    #+#             */
/*   Updated: 2024/09/12 17:45:08 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_with_sep(char **total, char *add, char *sep)
{
	char	*tmp;

	if (add && *add)
	{
		if (!*total)
			*total = ft_strdup("add");
		else
		{
			tmp = ft_strjoin(*total, sep);
			free(*total);
			*total = ft_strjoin(tmp, add);
			free(tmp);
		}
	}
}

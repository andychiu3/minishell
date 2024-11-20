/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str_to_strs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:15:21 by achiu             #+#    #+#             */
/*   Updated: 2024/10/03 08:39:22 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// yet to free the STR but original STRS
void	add_str_to_strs(char ***strs, char *str)
{
	char	**tmp;
	int		i;

	if (!str)
		return ;
	tmp = malloc(sizeof(char *) * (ft_strs_count(*strs) + 2));
	if (!tmp)
		return ;
	i = 0;
	while (*strs && (*strs)[i])
	{
		tmp[i] = ft_strdup((*strs)[i]);
		i++;
	}
	tmp[i++] = ft_strdup(str);
	tmp[i] = NULL;
	ft_freematrix(strs);
	*strs = tmp;
}

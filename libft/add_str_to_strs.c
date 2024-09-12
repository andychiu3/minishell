/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str_to_strs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <achiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:15:21 by achiu             #+#    #+#             */
/*   Updated: 2024/09/12 19:15:36 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_str_to_strs(char ***strs, char *str)
{
	char	**tmp;
	int		i;

	if (!str)
		return ;
	tmp = malloc(sizeof(char *) * (ft_strs_count(*strs) + 2));
	if (!tmp)
		return ;
	i = -1;
	while ((*strs)[++i])
		tmp[i] = ft_strdup((*strs)[i]);
	tmp[i++] = ft_strdup(str);
	tmp[i] = NULL;
	ft_freematrix(*strs);
	*strs = tmp;
}

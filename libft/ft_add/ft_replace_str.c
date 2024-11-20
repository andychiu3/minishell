/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:04:37 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/07 21:21:50 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace_str(char **old, char *new)
{
	if (!*old)
	{
		*old = new;
		return ;
	}
	free(*old);
	*old = new;
}

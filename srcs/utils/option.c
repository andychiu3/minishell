/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 07:53:16 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/13 08:03:23 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_option(char *arg, char c)
{
	int	i;

	if (!arg || !arg[0] || arg[0] != '-' || !arg[1] || arg[1] != c)
		return (0);
	i = 2;
	while (arg[i] && arg[i] == c)
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

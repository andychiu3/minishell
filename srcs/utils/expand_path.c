/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:24:08 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/08 09:16:14 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_path(char **str)
{
	char	*path;
	char	*tmp;

	if (!*str)
		return ;
	path = NULL;
	if (ft_strcmp("~", *str) == 0)
		path = ft_strdup(getenv("HOME"));
	else if (ft_strncmp("~/", *str, 2) == 0)
	{
		tmp = ft_strjoin(getenv("HOME"), "/");
		path = ft_strjoin(tmp, *str + 2);
		free(tmp);
	}
	if (path)
		ft_replace_str(str, path);
}

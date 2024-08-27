/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:05:44 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/27 09:06:22 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_sh *sh, char *target)
{
	int		i;
	size_t	len;

	len = ft_strlen(target);
	i = -1;
	while (sh->env[++i])
		if (ft_strncmp(target, sh->env[i], len) == 0 && sh->env[i][len] == '=')
			return (ft_strchr(sh->env[i], '=') + 1);
	return (NULL);
}

// STRDUP needed if we r gonna change/use env
int	init_env(t_sh *sh, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	sh->env = malloc(sizeof(char *) * (i + 1));
	if (!sh->env)
		return (0);
	i = -1;
	while (env[++i])
		sh->env[i] = ft_strdup(env[i]);
	return (1);
}

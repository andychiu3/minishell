/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:07:08 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 12:23:00 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var(char ***strs, t_sh *sh)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = -1;
	while ((*strs)[++i])
	{
		if ((*strs)[i][0] == '$' && (*strs)[i][1] == '?')
		{
			free((*strs)[i]);
			(*strs)[i] = ft_itoa(*(sh->ret));
		}
		else if ((*strs)[i][0] == '$'
			&& (ft_isalnum((*strs)[i][1]) || (*strs)[i][1] == '_'))
		{
			tmp = (*strs)[i] + 1;
			tmp = get_env_value(sh, tmp);
			free((*strs)[i]);
			if (tmp)
				(*strs)[i] = ft_strdup(tmp);
			else
				(*strs)[i] = ft_strdup("");
		}
	}
}

char	*var_situation(char *str, t_sh *sh)
{
	char	**strs;
	char	*new;
	int		i;
	char	*tmp;

	if (!str)
		return (NULL);
	strs = split_by_var(str);
	if (!strs)
		return (NULL);
	replace_var(&strs, sh);
	new = ft_strdup("");
	i = -1;
	while (++i < split_count(str))
	{
		tmp = new;
		new = ft_strjoin(new, strs[i]);
		free(tmp);
	}
	ft_freematrix(&strs);
	return (new);
}

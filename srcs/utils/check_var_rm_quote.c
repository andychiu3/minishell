/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_rm_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:04:43 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/09 07:50:10 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_strs_quote(char **strs)
{
	int		i;
	char	*new;

	if (!strs)
		return ;
	i = -1;
	while (strs[++i])
	{
		new = remove_quote(strs[i]);
		ft_replace_str(&strs[i], new);
	}
}

// return 1 if ambigious
int	check_var(char **str, t_sh *sh)
{
	char	*tmp;
	int		has_var;

	if (!str || !*str)
		return (0);
	has_var = (ft_strchr(*str, '$') != NULL);
	tmp = var_situation(*str, sh);
	if (ft_strcmp(tmp, "") == 0 && has_var)
	{
		if (tmp)
			free(tmp);
		return (1);
	}
	ft_replace_str(str, tmp);
	return (0);
}

// return 1 if ambigious
int	check_var_rm_quote(char **str, t_sh *sh)
{
	char	*tmp;
	int		has_var;

	if (!str || !*str)
		return (0);
	has_var = (ft_strchr(*str, '$') != NULL);
	tmp = var_situation(*str, sh);
	if (ft_strcmp(tmp, "") == 0 && has_var)
	{
		if (tmp)
			free(tmp);
		return (1);
	}
	free(*str);
	if (tmp)
	{
		*str = remove_quote(tmp);
		free(tmp);
	}
	else
		*str = NULL;
	return (0);
}

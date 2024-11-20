/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 09:16:04 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/10 19:28:30 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_name(char *arg)
{
	int	name_ends;

	if (!arg)
		return (NULL);
	name_ends = 0;
	while (arg[name_ends] && arg[name_ends] != '=')
	{
		if ((arg[name_ends] == '+' && arg[name_ends + 1] == '='))
			break ;
		name_ends++;
	}
	return (ft_substr(arg, 0, name_ends));
}

// do NOT free this ptr
char	*new_value(char *arg)
{
	char	*pos_eq;

	if (!arg)
		return (NULL);
	pos_eq = ft_strchr(arg, '=');
	if (pos_eq)
		return (pos_eq + 1);
	return (NULL);
}

// return 2 if same var but diff value
// return 1 if var AND value r the same
// return 0 if var doesn't exist then 
int	compare_env_var(char *env, char *arg)
{
	char	*env_var;
	char	*new_var;

	if (!env || !arg)
		return (-1);
	if (ft_strcmp(env, arg) == 0)
		return (1);
	env_var = env_name(env);
	new_var = new_name(arg);
	if (!env_var || !new_var)
		return (free(env_var), free(new_var), -1);
	if (ft_strcmp(env_var, new_var) == 0)
		return (free(env_var), free(new_var), 2);
	free(env_var);
	free(new_var);
	return (0);
}

int	pos_of_env_var(char *arg, t_sh *sh)
{
	int	i;

	i = -1;
	while (sh->env && sh->env[++i])
	{
		if (compare_env_var(sh->env[i], arg) == 1
			|| compare_env_var(sh->env[i], arg) == 2)
			return (i);
	}
	return (-1);
}

// -2: OPTION
// -1: INVALID
// 0: NOEQ
// return 1 if valid
// return 2 if needs adding up
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] && (str[i] == '_' || ft_isalpha(str[i])))
	{
		i++;
		while (str[i] && str[i] != '=')
		{
			if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
				return (2);
			else if ((str[i] != '_' && !ft_isalnum(str[i])))
				return (-1);
			i++;
		}
		return (str[i] == '=');
	}
	else if (str[i] && str[i] == '-' && str[i + 1])
		return (-2);
	return (-1);
}

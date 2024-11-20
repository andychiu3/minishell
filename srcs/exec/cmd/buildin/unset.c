/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:41:53 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 21:21:42 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_var(char *env, char *arg)
{
	char	*env_var;

	if (!env || !arg)
		return (-1);
	env_var = env_name(env);
	if (!env_var)
		return (-1);
	if (ft_strcmp(env_var, arg) == 0)
	{
		free(env_var);
		return (1);
	}
	free(env_var);
	return (0);
}

void	rm_env_var(char *arg, t_sh *sh)
{
	char	**tmp;
	int		i;
	int		j;

	if (!sh || !arg)
		return ;
	tmp = malloc(sizeof(char *) * (ft_strs_count(sh->env)));
	if (!tmp)
		return ;
	i = -1;
	j = 0;
	while (sh->env[++i])
		if (compare_var(sh->env[i], arg) != 1)
			tmp[j++] = ft_strdup(sh->env[i]);
	tmp[j] = NULL;
	ft_freematrix(&sh->env);
	sh->env = tmp;
}

void	exec_unset(char *arg, t_sh *sh)
{
	int	i;
	int	var_exist;

	if (!arg || !sh || !sh->env)
		return ;
	if (is_valid_identifier(arg) == 0)
	{
		i = -1;
		var_exist = 0;
		while (sh->env[++i])
			if (compare_var(sh->env[i], arg) == 1)
				var_exist = 1;
		if (var_exist)
			rm_env_var(arg, sh);
		*(sh->ret) = 0;
	}
	// else if (is_valid_identifier(arg) == -1 || is_valid_identifier(arg) == 1)
	// 	builtin_err_cases("unset: invalid", 1, arg, sh);
	// else if (is_valid_identifier(arg) == -2)
	// 	builtin_err_cases("unset: option", 2, arg, sh);
}

void	process_unset(t_cmd *cmd, t_sh *sh)
{
	int	i;

	if (!cmd || !sh || !cmd->arg)
		return ;
	i = -1;
	while (cmd->arg[++i])
		exec_unset(cmd->arg[i], sh);
}

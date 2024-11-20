/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:12:45 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 12:15:18 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_(char *arg, t_sh *sh)
{
	char	*var;
	char	*value;
	char	*tmp;

	var = new_name(arg);
	if (!var)
		return ;
	value = new_value(arg);
	if (!value)
		return ;
	if (!*value)
	{
		tmp = var;
		var = ft_strjoin(tmp, "=");
		free(tmp);
	}
	else
		ft_strjoin_with_sep(&var, value, "=");
	add_str_to_strs(&sh->env, var);
}

void	var_value_adding(char *arg, t_sh *sh)
{
	int		i;
	char	*tmp;
	char	*addup;

	addup = new_value(arg);
	if (!addup)
		return ;
	i = pos_of_env_var(arg, sh);
	if (i == -1 || !sh->env)
		update_env_(arg, sh);
	if (!*addup)
		return ;
	if (i != -1)
	{
		tmp = sh->env[i];
		sh->env[i] = ft_strjoin(tmp, addup);
		free(tmp);
	}
}

void	var_value_changing(char *arg, t_sh *sh)
{
	int	pos_var;

	pos_var = pos_of_env_var(arg, sh);
	if (pos_var == -1 || !sh->env)
		add_str_to_strs(&(sh->env), arg);
	else if (compare_env_var(sh->env[pos_var], arg) == 2)
	{
		free(sh->env[pos_var]);
		sh->env[pos_var] = ft_strdup(arg);
		return ;
	}
	else if (compare_env_var(sh->env[pos_var], arg) == 1)
		return ;
}

// only be used if arg n sh valid cuz too many lines
void	exec_export(char *arg, t_sh *sh)
{
	if (is_valid_identifier(arg) == 2)
	{
		var_value_adding(arg, sh);
		*(sh->ret) = 0;
	}
	else if (is_valid_identifier(arg) == 1)
	{
		var_value_changing(arg, sh);
		*(sh->ret) = 0;
	}
	else if (is_valid_identifier(arg) == -1)
		builtin_err_cases("export: invalid", 1, arg, sh);
	else if (is_valid_identifier(arg) == -2)
		builtin_err_cases("export: option", 2, arg, sh);
}

void	process_export(t_cmd *cmd, t_sh *sh)
{
	int		i;
	char	*eq_pos;

	if (!cmd || !sh)
		return ;
	i = -1;
	while (cmd->arg && cmd->arg[++i])
		exec_export(cmd->arg[i], sh);
	if (!cmd->arg && cmd->cmd)
	{
		i = -1;
		while (sh->env && sh->env[++i])
		{
			eq_pos = ft_strchr(sh->env[i], '=');
			if (eq_pos)
				printf("declare -x %.*s=\"%s\"\n",
					(int)(eq_pos - sh->env[i]), sh->env[i], eq_pos + 1);
		}
	}
}

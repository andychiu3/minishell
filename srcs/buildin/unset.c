/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:41:53 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/16 16:16:25 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (compare_env_var(sh->env[i], arg) != -1)
			tmp[j++] = ft_strdup(sh->env[i]);
	tmp[j] = NULL;
	ft_freematrix(sh->env);
	sh->env = tmp;
}

void	exec_unset(char *arg, t_sh *sh)
{
	int	i;
	int	var_exist;

	if (!arg || !sh)
		return ;
	if (is_valid_identifier(arg) == 0)
	{
		i = -1;
		var_exist = 0;
		while (sh->env[++i])
			if (compare_env_var(sh->env[i], arg) == -1)
				var_exist = 1;
		if (var_exist)
			rm_env_var(arg, sh);
		g_last_exit_code = 0;
	}
	else
		errormsg_exitcode("unset", 1, arg);
}

void	process_unset(t_cmd *cmd, t_sh *sh)
{
	int	i;

	if (!cmd || !sh)
		return ;
	i = -1;
	while (cmd->arg[++i])
		exec_unset(cmd->arg[i], sh);
}

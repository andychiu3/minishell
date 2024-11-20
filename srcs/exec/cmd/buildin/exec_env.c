/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:32:18 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 12:14:18 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_cmd *cmd, int in_fd, int out_fd, t_sh *sh)
{
	int	i;

	if (!cmd)
		return ;
	(void)in_fd;
	(void)out_fd;
	i = -1;
	if (cmd->arg)
	{
		if (ft_strcmp("=", *cmd->arg) == 0
			|| ft_strncmp("-", *cmd->arg, 1) == 0)
			builtin_err_cases(cmd->cmd, 1, *cmd->arg, sh);
		else
			builtin_err_cases(cmd->cmd, 1, *cmd->arg, sh);
		return ;
	}
	while (sh->env && sh->env[++i])
		ft_putendl_fd(sh->env[i], STDOUT_FILENO);
	*(sh->ret) = 0;
}

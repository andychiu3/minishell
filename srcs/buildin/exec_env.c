/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:32:18 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/16 13:39:22 by fiftyblue        ###   ########.fr       */
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
			errormsg_exitcode(cmd->cmd, 1, *cmd->arg);
		else
			errormsg_exitcode(cmd->cmd, 127, *cmd->arg);
		return ;
	}
	while (sh->env[++i])
		ft_putendl_fd(sh->env[i], STDOUT_FILENO);
}

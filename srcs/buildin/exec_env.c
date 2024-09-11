/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:32:18 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/11 09:32:32 by fiftyblue        ###   ########.fr       */
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
		printf("minishell: cd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	while (sh->env[++i])
		ft_putendl_fd(sh->env[i], STDOUT_FILENO);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:33:45 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/16 21:27:47 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(t_cmd *cmd)
{
	int	exit_nbr;

	if (!cmd)
		return ;
	exit_nbr = 0;
	if (cmd->arg)
	{
		if (ft_isnbr(cmd->arg[0]))
			exit_nbr = ft_atoi(cmd->arg[0]);
		else
		{
			err_printf("minishell: exit: %s: numeric argument required\n",
				cmd->arg[0]);
			exit_nbr = 1;
			exit(exit_nbr % 256);
		}
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->arg && cmd->arg[1])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		exit_nbr = 1;
	}
	exit(exit_nbr % 256);
}


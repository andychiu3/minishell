/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:33:45 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 21:21:29 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_nbr_err_case(t_cmd *cmd, t_sh *sh)
{
	if (!cmd)
		return ;
	if (cmd->arg)
	{
		if (ft_isnbr(cmd->arg[0]))
			*(sh->ret) = ft_atoi(cmd->arg[0]);
		else
		{
			err_printf("minishell: exit: %s: numeric argument required\n",
				cmd->arg[0]);
			*(sh->ret) = 2;
			return ;
		}
	}
	if (cmd->arg && cmd->arg[1])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		*(sh->ret) = 1;
	}
}

void	exec_exit(t_cmd *cmd, t_sh *sh)
{
	if (!sh->pipe_in && !sh->pipe_out)
	{
		ft_putendl_fd("exit", *(sh->ret));
		exit_nbr_err_case(cmd, sh);
		exit(*(sh->ret));
	}
	else
		exit_nbr_err_case(cmd, sh);
}

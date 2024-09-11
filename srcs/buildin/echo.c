/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:33:15 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/11 09:35:54 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_cmd *cmd, int in_fd, int out_fd)
{
	int	i;
	int	nextline;

	if (!cmd || !cmd->arg)
		return ;
	(void)in_fd;
	nextline = 1;
	i = 0;
	if (ft_strcmp("-n", cmd->arg[i]) == 0)
	{
		nextline = 0;
		i++;
	}
	while (cmd->arg[i])
	{
		if (cmd->arg[i])
			ft_putstr_fd(cmd->arg[i], out_fd);
		if (cmd->arg[i + 1])
			ft_putchar_fd(' ', out_fd);
		i++;
	}
	if (nextline)
		ft_putchar_fd('\n', out_fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:33:15 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 12:14:06 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	echo_option(char *arg)
// {
// 	int	i;

// 	if (!arg || ft_strncmp("-n", arg, 2) != 0)
// 		return (0);
// 	i = 2;
// 	while (arg[i] && arg[i] == 'n')
// 		i++;
// 	if (arg[i] == '\0')
// 		return (1);
// 	return (0);
// }

void	exec_echo(t_cmd *cmd, t_sh *sh)
{
	int	i;
	int	nextline;

	if (!cmd)
		return ;
	nextline = 1;
	if (cmd->arg)
	{
		i = -1;
		while (cmd->arg[++i] && validate_option(cmd->arg[i], 'n') == 1)
			nextline = 0;
		while (cmd->arg[i])
		{
			if (cmd->arg[i])
				ft_putstr_fd(cmd->arg[i], STDOUT_FILENO);
			if (cmd->arg[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (nextline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	*(sh->ret) = 0;
}

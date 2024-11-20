/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:34:06 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 12:19:25 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_cmd *cmd, t_sh *sh)
{
	char	*pwd;

	if (!cmd)
		return ;
	(void)sh;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free (pwd);
	}
	*(sh->ret) = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:34:06 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/16 16:16:37 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_cmd *cmd, int in_fd, int out_fd)
{
	char	*pwd;

	if (!cmd)
		return ;
	(void)in_fd;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, out_fd);
		free (pwd);
	}
	g_last_exit_code = 0;
}

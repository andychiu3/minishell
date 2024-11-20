/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:15:02 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 19:21:46 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// yet to consider the full path
int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

void	builtin(t_cmd *cmd, int in_fd, int out_fd, t_sh *sh)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		exec_echo(cmd, sh);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		exec_pwd(cmd, sh);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		exec_env(cmd, in_fd, out_fd, sh);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		process_export(cmd, sh);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		process_unset(cmd, sh);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		process_cd(cmd, sh);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		exec_exit(cmd, sh);
}

void	setup_builtin(t_cmd *cmd, int in_fd, int out_fd, t_sh *sh)
{
	pid_t	pid;
	int		status;

	if (!sh->pipe_in && !sh->pipe_out)
		builtin(cmd, in_fd, out_fd, sh);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			sig_mode(IN_CHILD);
			builtin(cmd, in_fd, out_fd, sh);
			exit(*(sh->ret));
		}
		else if (pid > 0)
		{
			if (sh->pipe_out)
				sig_mode(IN_CHILD);
			waitpid(pid, &status, 0);
			waitpid_status(&status, sh);
		}
	}
}

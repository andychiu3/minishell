/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:01:48 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 21:14:20 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_n_backup_std_io(int *in_fd, int *out_fd, int *saved_fd)
{
	if (*in_fd != STDIN_FILENO)
	{
		if (saved_fd && saved_fd[0] == -1)
			saved_fd[0] = dup(STDIN_FILENO);
		dup2(*in_fd, STDIN_FILENO);
		close(*in_fd);
	}
	if (*out_fd != STDOUT_FILENO)
	{
		if (saved_fd && saved_fd[1] == -1)
			saved_fd[1] = dup(STDOUT_FILENO);
		dup2(*out_fd, STDOUT_FILENO);
		close(*out_fd);
	}
}

void	restore_std_io(int in_fd, int out_fd, int *saved_fd)
{
	if (saved_fd[0] != -1)
	{
		if (in_fd != STDIN_FILENO)
			dup2(saved_fd[0], STDIN_FILENO);
		close(saved_fd[0]);
		saved_fd[0] = -1;
	}
	if (saved_fd[1] != -1)
	{
		if (out_fd != STDOUT_FILENO)
			dup2(saved_fd[1], STDOUT_FILENO);
		close(saved_fd[1]);
		saved_fd[1] = -1;
	}
}

void	close_unuse_fd(int *in_fd, int *out_fd)
{
	if (*in_fd != STDIN_FILENO && *in_fd > 0)
	{
		close(*in_fd);
		*in_fd = -1;
	}
	if (*out_fd != STDOUT_FILENO && *out_fd > 0)
	{
		close(*out_fd);
		*out_fd = -1;
	}
}

// 2 cases: builtin or execve
void	exec_cmd(t_ast *root, int *in_fd, int *out_fd, t_sh *sh)
{
	t_cmd	*cmd;
	int		saved_fd[2];

	if (!root)
		return ;
	cmd = (t_cmd *)root->content;
	refresh_cmd(cmd, sh);
	if (!cmd->cmd)
		return (close_unuse_fd(in_fd, out_fd));
	saved_fd[0] = -1;
	saved_fd[1] = -1;
	if (is_builtin(cmd->cmd))
	{
		redir_n_backup_std_io(in_fd, out_fd, saved_fd);
		setup_builtin(cmd, *in_fd, STDOUT_FILENO, sh);
	}
	else
		fork_for_execve(root, in_fd, out_fd, sh);
	restore_std_io(*in_fd, *out_fd, saved_fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:01:48 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/15 11:06:45 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_n_backup_std_io(int *in_fd, int *out_fd, int *saved_fd)
{
	if (*in_fd != STDIN_FILENO)
	{
		if (saved_fd && *saved_fd == -1)
			*saved_fd = dup(STDIN_FILENO);
		dup2(*in_fd, STDIN_FILENO);
		close(*in_fd);
	}
	if (*out_fd != STDOUT_FILENO)
	{
		if (saved_fd && *saved_fd == -1)
			*saved_fd = dup(STDOUT_FILENO);
		dup2(*out_fd, STDOUT_FILENO);
		close(*out_fd);
	}
}

void	restore_std_io(int in_fd, int out_fd, int saved_fd)
{
	if (saved_fd != -1)
	{
		if (out_fd != STDOUT_FILENO)
			dup2(saved_fd, STDOUT_FILENO);
		else if (in_fd != STDIN_FILENO)
			dup2(saved_fd, STDIN_FILENO);
		close(saved_fd);
	}
}

// parent process after forking for cmd
// also update the exit code
void	close_unuse_fd(int *in_fd, int *out_fd)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
}

// do we need exit(EXIT_SUCCESS); or other checker
void	fork_for_execve(t_ast *root, int *in_fd, int *out_fd, t_sh *sh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		redir_n_backup_std_io(in_fd, out_fd, NULL);
		exec_with_execve((t_cmd *)root->content, sh);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close_unuse_fd(in_fd, out_fd);
		waitpid(pid, &status, 0);
		g_last_exit_code = WEXITSTATUS(status);
	}
}

// check 3 situation: builtin, execve and cmd not found
void	exec_cmd(t_ast *root, int in_fd, int out_fd, t_sh *sh)
{
	t_cmd	*cmd;
	int		saved_fd;

	if (!root)
		return ;
	cmd = (t_cmd *)root->content;
	saved_fd = -1;
	if (is_builtin(cmd->cmd))
	{
		redir_n_backup_std_io(&in_fd, &out_fd, &saved_fd);
		builtin(cmd, in_fd, STDOUT_FILENO, sh);
	}
	else if (is_executable(cmd->cmd, sh))
		fork_for_execve(root, &in_fd, &out_fd, sh);
	else
		errormsg_exitcode("nocmd", 127, cmd->cmd);
	restore_std_io(in_fd, out_fd, saved_fd);
}

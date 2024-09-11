/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:01:48 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/11 16:36:26 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	before_cmd(int *in_fd, int *out_fd)
{
	if (*in_fd != STDIN_FILENO)
	{
		dup2(*in_fd, STDIN_FILENO);
		close(*in_fd);
	}
	if (*out_fd != STDOUT_FILENO)
	{
		dup2(*out_fd, STDOUT_FILENO);
		close(*out_fd);
	}
}

// parent process after forking for cmd
// also update the exit code
void	wait_for_child(int *in_fd, int *out_fd, pid_t pid)
{
	int		status;

	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	waitpid(pid, &status, 0);
	g_last_exit_code = WEXITSTATUS(status);
}

// any error occurrs would not get to the line: exit(EXIT_SUCCESS);
void	fork_for_execve(t_ast *root, int *in_fd, int *out_fd, t_sh *sh)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		before_cmd(in_fd, out_fd);
		exec_with_execve((t_cmd *)root->content, sh);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
		wait_for_child(in_fd, out_fd, pid);
}

// check 3 situation: builtin, execve and cmd not found
void	exec_cmd(t_ast *root, int in_fd, int out_fd, t_sh *sh)
{
	t_cmd	*cmd;
	int		saved_stdout;

	if (!root)
		return ;
	cmd = (t_cmd *)root->content;
	saved_stdout = dup(STDOUT_FILENO);
	if (is_builtin(cmd->cmd))
	{
		before_cmd(&in_fd, &out_fd);
		builtin(cmd, in_fd, STDOUT_FILENO, sh);
	}
	else if (is_executable(cmd->cmd, sh))
		fork_for_execve(root, &in_fd, &out_fd, sh);
	else
		errormsg_exitcode("nocmd", 1, cmd->cmd);
	if (out_fd != STDOUT_FILENO)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

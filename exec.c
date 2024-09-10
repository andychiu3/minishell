/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:18:17 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/10 18:39:25 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_ast *root, int in_fd, int out_fd, t_sh *sh)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		exec_ast(root->left, in_fd, pipe_fd[1], sh);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		exec_ast(root->right, pipe_fd[0], out_fd, sh);
		close(pipe_fd[0]);
		printf("exec_pipe: hi\n");
	}
}

// 0644 means rw-r--r--
// void	process_redir(t_ast *root, int in_fd, int out_fd, t_sh *sh)
// {
// 	t_redirect		*redir;
// 	int				fd;

// 	fd = -1;
// 	if (root->type == INPUT)
// 	{
// 		redir = (t_redirect *)(root->content);
// 		fd = open(redir->file, O_RDONLY);
// 		if (fd == -1)
// 			return ;
// 		in_fd = fd;
// 	}
// 	else if (root->type == TRUNC)
// 	{
// 		redir = (t_redirect *)(root->content);
// 		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 			return ;
// 		if (out_fd != STDOUT_FILENO)
// 			close(out_fd);
// 		out_fd = fd;
// 	}
// 	else if (root->type == APPEND)
// 	{
// 		redir = (t_redirect *)(root->content);
// 		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 			return ;
// 		if (out_fd != STDOUT_FILENO)
// 			close(out_fd);
// 		out_fd = fd;
// 	}
// 	if (root->right && is_redirect(root->right->type))
// 		process_redir(root->right, in_fd, out_fd, sh);
// 	if (root->left && root->left->type == CMD)
// 		process_cmd(root->left, in_fd, out_fd, sh);
// 	if (fd != -1)
// 		close (fd);
// }

//	if (WIFEXITED(status))
//		printf("Child exited normally with status %d\n", WEXITSTATUS(status));
//	else if (WIFSIGNALED(status))
//		printf("Child terminated by signal %d\n", WTERMSIG(status));
//	else if (WIFSTOPPED(status))
//		printf("Child stopped by signal %d\n", WSTOPSIG(status));
//	else
//		printf("Child exited for unknown reason\n");
void	process_cmd(t_ast *root, int in_fd, int out_fd, t_sh *sh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		exec_cmd(root, STDIN_FILENO, STDOUT_FILENO, sh);
		// printf("process_cmd child: hi\n");
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		waitpid(pid, &status, 0);
		// printf("process_cmd parent: hi\n");
		g_last_exit_code = WEXITSTATUS(status);
	}
}

void	exec_ast(t_ast *root, int in_fd, int out_fd, t_sh *sh)
{
	if (!root)
		return ;
	if (root->type == PIPE)
		exec_pipe(root, in_fd, out_fd, sh);
	else if (is_redirect(root->type))
		process_redir(root, &in_fd, &out_fd, sh);
	else if (root->type == CMD)
		process_cmd(root, in_fd, out_fd, sh);
}

// void	exec_ast(t_ast *root, int in_fd, int out_fd)
// {
// 	int	pipe_fd[2];

// 	if (!root)
// 		return ;
// 	if (root->type == PIPE)
// 	{
// 		pipe(pipe_fd);
// 		exec_ast(root->left, in_fd, pipe_fd[1]);
// 		close(pipe_fd[1]);
// 		exec_ast(root->right, pipe_fd[0], out_fd]);
// 		close(pipe_fd[0]);
// 	}
// 	else if (is_redirect(root->type))
// 		exec_redir();
// 	else if (root->type == CMD)
// 		exec_cmd(root, in_fd, out_fd);
// 	exec_ast(root->right);
// }

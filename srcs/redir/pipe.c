/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:24:53 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/14 08:06:19 by fiftyblue        ###   ########.fr       */
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
		// printf("exec_pipe: out_fd: %d\n", out_fd);
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
	}
}

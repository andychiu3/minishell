/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <achiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:24:26 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/12 19:05:16 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_input(t_redirect *redir, int *in_fd)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return ;
	if (*in_fd != STDIN_FILENO)
		close (*in_fd);
	*in_fd = fd;
}

void	exec_trunc(t_redirect *redir, int *out_fd)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (*out_fd != STDOUT_FILENO)
		close (*out_fd);
	*out_fd = fd;
}

void	exec_append(t_redirect *redir, int *out_fd)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	if (*out_fd != STDOUT_FILENO)
		close (*out_fd);
	*out_fd = fd;
}

void	process_redir(t_ast *root, int *in_fd, int *out_fd, t_sh *sh)
{
	t_redirect		*redir;

	redir = (t_redirect *)(root->content);
	if (root->type == INPUT)
		exec_input(redir, in_fd);
	else if (root->type == TRUNC)
		exec_trunc(redir, out_fd);
	else if (root->type == APPEND)
		exec_append(redir, out_fd);
	else if (root->type == APPEND)
		fork_for_heredoc(redir, in_fd, sh);
	if (root->right && is_redirect(root->right->type))
		process_redir(root->right, in_fd, out_fd, sh);
	if (root->left && root->left->type == CMD)
		exec_cmd(root->left, *in_fd, *out_fd, sh);
}

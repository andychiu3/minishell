/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:24:26 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 12:21:14 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_err(char *file, int ambiguous, t_sh *sh)
{
	struct stat	path_stat;

	if (ambiguous == 1)
		err_printf("minishell: %s: ambiguous redirect\n", file);
	else if (stat(file, &path_stat) == -1)
		err_printf("minishell: %s: No such file or directory\n", file);
	else if (S_ISDIR(path_stat.st_mode))
		err_printf("minishell: %s: Is a directory\n", file);
	else
		err_printf("minishell: %s: Permission denied\n", file);
	*(sh->ret) = 1;
	return (-1);
}

int	process_redir(t_ast **root, int *in_fd, int *out_fd, t_sh *sh)
{
	t_redirect		*redir;
	int				result;
	int				l_result;

	redir = (t_redirect *)((*root)->content);
	result = 0;
	if ((*root)->type == INPUT)
		result = exec_input(redir, in_fd, sh);
	else if ((*root)->type == TRUNC)
		result = exec_trunc(redir, out_fd, sh);
	else if ((*root)->type == APPEND)
		result = exec_append(redir, out_fd, sh);
	else if ((*root)->type == HEREDOC)
		result = exec_heredoc(redir, in_fd);
	if (result != 0)
		return (result);
	if ((*root)->left && is_redirect((*root)->left->type))
	{
		l_result = process_redir(&(*root)->left, in_fd, out_fd, sh);
		if (l_result != 0)
			return (l_result);
	}
	return (0);
}

void	redir(t_ast *root, int *in_fd, int *out_fd, t_sh *sh)
{
	if (process_redir(&root, in_fd, out_fd, sh) == 0
		&& root->right && root->right->type == CMD)
		exec_cmd(root->right, in_fd, out_fd, sh);
	else
		close_unuse_fd(in_fd, out_fd);
}

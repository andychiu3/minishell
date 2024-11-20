/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:08:21 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 11:52:05 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_trunc(t_redirect *redir, int *out_fd, t_sh *sh)
{
	int	fd;
	int	ambiguous;

	ambiguous = check_var_rm_quote(&redir->file, sh);
	if (ambiguous)
		return (redir_err(redir->file, ambiguous, sh));
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (redir_err(redir->file, ambiguous, sh));
	if (*out_fd != STDOUT_FILENO)
		close (*out_fd);
	*out_fd = fd;
	return (0);
}

int	exec_append(t_redirect *redir, int *out_fd, t_sh *sh)
{
	int	fd;
	int	ambiguous;

	ambiguous = check_var_rm_quote(&redir->file, sh);
	if (ambiguous)
		return (redir_err(redir->file, ambiguous, sh));
	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (redir_err(redir->file, ambiguous, sh));
	if (*out_fd != STDOUT_FILENO)
		close (*out_fd);
	*out_fd = fd;
	return (0);
}

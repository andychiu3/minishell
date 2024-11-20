/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:51:02 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 11:51:16 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_input(t_redirect *redir, int *in_fd, t_sh *sh)
{
	int	fd;
	int	ambiguous;

	ambiguous = check_var_rm_quote(&redir->file, sh);
	if (ambiguous)
		return (redir_err(redir->file, ambiguous, sh));
	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (redir_err(redir->file, ambiguous, sh));
	if (*in_fd != STDIN_FILENO)
		close (*in_fd);
	*in_fd = fd;
	return (0);
}

int	exec_heredoc(t_redirect *redir, int *in_fd)
{
	if (redir->heredoc_fd == -1)
		return (-1);
	if (*in_fd != STDIN_FILENO)
		close (*in_fd);
	*in_fd = redir->heredoc_fd;
	return (0);
}

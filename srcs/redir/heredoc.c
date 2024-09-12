/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <achiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:47:43 by achiu             #+#    #+#             */
/*   Updated: 2024/09/12 19:06:05 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_strjoin_with_sep(char **total, char *add, char *sep)
// {
// 	char	*tmp;

// 	if (add && *add)
// 	{
// 		if (!*total)
// 			*total = ft_strdup("add");
// 		else
// 		{
// 			tmp = ft_strjoin(*total, sep);
// 			free(*total);
// 			*total = ft_strjoin(tmp, add);
// 			free(tmp);
// 		}
// 	}
// }

// no freeing for add but original total
void	strjoin_after_nextline(char **total, char *add)
{
	char	*tmp;

	if (add && *add)
	{
		if (!*total)
			*total = ft_strdup("add");
		else
		{
			tmp = ft_strjoin(*total, "\n");
			free(*total);
			*total = ft_strjoin(tmp, add);
			free(tmp);
		}
	}
}

void	free_n_exit(char *input, int exit_code)
{
	if (input)
		free(input);
	exit(exit_code);
}

// var situation??
void	heredoc(t_redirect *redir, int pipe_o, t_sh *sh)
{
	char		*line;
	char		*input;

	if (!redir)
		return ;
	input = NULL;
	(void)sh;
	while (1)
	{
		line = readline("> ");
		if (!line)
			free_n_exit(input, EXIT_FAILURE);
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		ft_strjoin_with_sep(&input, line, "\n");
		free(line);
	}
	ft_putstr_fd(input, pipe_o);
	close(pipe_o);
	free_n_exit(input, EXIT_SUCCESS);
}

void	fork_for_heredoc(t_redirect *redir, int *in_fd, t_sh *sh)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		heredoc(redir, pipe_fd[1], sh);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipe_fd[0], *in_fd);
		close(pipe_fd[0]);
	}
	else
		perror("fork failed");
}

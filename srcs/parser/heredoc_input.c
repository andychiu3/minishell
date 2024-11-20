/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:18:51 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 11:59:43 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -1: EOF errormsg print
// 0: consider var_situation
// 1: in quote so no var_situation
int	parse_dlmtr(t_redirect *redir, char **delimiter, t_sh *sh)
{
	if (ft_strchr(redir->file, '\'') || ft_strchr(redir->file, '\"'))
	{
		if (!quote_valid(redir->file, sh))
			return (-1);
		else
		{
			*delimiter = remove_quote(redir->file);
			return (1);
		}
	}
	*delimiter = ft_strdup(redir->file);
	return (0);
}

void	heredoc_input(char *dlmtr, t_sh *sh, int quote_case, char **input)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		line = get_line("> ", 0, NULL, sh);
		if (sh->signaled)
			free_n_exit(*input, dlmtr, EXIT_FAILURE);
		if (ft_strcmp(line, dlmtr) == 0)
		{
			free(line);
			break ;
		}
		if (quote_case == 0)
		{
			tmp = line;
			line = var_situation(tmp, sh);
			free(tmp);
		}
		add_str_with_nextline(input, line);
		free(line);
	}
}

void	setup_heredoc(t_redirect *redir, int pipe_o, t_sh *sh)
{
	char	*input;
	char	*dlmtr;
	int		quote_case;

	if (!redir)
		return ;
	input = NULL;
	dlmtr = NULL;
	quote_case = parse_dlmtr(redir, &dlmtr, sh);
	if (quote_case == -1)
	{
		close(pipe_o);
		exit(EXIT_FAILURE);
	}
	heredoc_input(dlmtr, sh, quote_case, &input);
	ft_putstr_fd(input, pipe_o);
	close(pipe_o);
	free_n_exit(input, dlmtr, EXIT_SUCCESS);
}

void	heredoc_result(t_redirect *redir, t_sh *sh, int status, int *pipe_fd)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		redir->heredoc_fd = pipe_fd[0];
	else
	{
		close(pipe_fd[0]);
		redir->heredoc_fd = -1;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			sh->signaled = 1;
	}
}

void	fork_for_heredoc(t_redirect *redir, t_sh *sh)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		signal(SIGINT, SIG_DFL);
		setup_heredoc(redir, pipe_fd[1], sh);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		heredoc_result(redir, sh, status, pipe_fd);
		if (!isatty(STDIN_FILENO))
			consume_stdin();
	}
}

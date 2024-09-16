/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:47:43 by achiu             #+#    #+#             */
/*   Updated: 2024/09/15 10:44:05 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -1: EOF errormsg print
// 0: consider var_situation
// 1: do nothing
int	in_delimiter(t_redirect *redir, char **delimiter)
{
	if (ft_strchr(redir->file, '\'') || ft_strchr(redir->file, '\"'))
	{
		if (!quote_valid(redir->file))
			return (-1);
		else
		{
			*delimiter = remove_quote(redir->file);
			printf("in_delimiter: redir->file: %s\n", redir->file);
			return (1);
		}
	}
	*delimiter = redir->file;
	return (0);
}

// no freeing for add but original total
void	add_str_with_nextline(char **total, char *add)
{
	char	*tmp;

	if (add && *add)
	{
		if (!*total)
			*total = ft_strjoin(add, "\n");
		else
		{
			tmp = ft_strjoin(*total, add);
			free(*total);
			*total = ft_strjoin(tmp, "\n");
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

void	heredoc_input(char *dlmtr, t_sh *sh, int in_deli, char **input)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	printf("heredoc input: dlmtr: %s\n", dlmtr);
	while (1)
	{
		line = readline("> ");
		if (!line)
			free_n_exit(*input, EXIT_FAILURE);
		if (ft_strcmp(line, dlmtr) == 0)
		{
			free(line);
			return ;
		}
		if (in_deli == 0)
		{
			tmp = line;
			line = var_situation(tmp, sh);
		}
		add_str_with_nextline(input, line);
		free(line);
		if (tmp)
			free(tmp);
	}
}

// var situation??
void	setup_heredoc(t_redirect *redir, int pipe_o, t_sh *sh)
{
	char	*input;
	char	*delimeter;
	int		in_deli;

	if (!redir)
		return ;
	input = NULL;
	delimeter = NULL;
	in_deli = in_delimiter(redir, &delimeter);
	if (in_deli == -1)
		exit(EXIT_FAILURE);
	heredoc_input(redir->file, sh, in_deli, &input);
	ft_putstr_fd(input, pipe_o);
	close(pipe_o);
	free_n_exit(input, EXIT_SUCCESS);
}

void	heredoc_(t_redirect *redir, int pipe_o, t_sh *sh)
{
	char	*line;
	char	*input;

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
		add_str_with_nextline(&input, line);
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
		setup_heredoc(redir, pipe_fd[1], sh);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		if (*in_fd != STDIN_FILENO)
			close(*in_fd);
		*in_fd = pipe_fd[0];
	}
	else
		perror("fork failed");
}

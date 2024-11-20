/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:13:54 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/11 09:20:42 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
wanna run the minishell as execve but already fork for heredoc
which means that both child and parent process will get STDIN_FILENO
and parent does not need it.

better solution might be not forking for heredoc but use the tmp_heredoc
*/
void	consume_stdin(void)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:35:44 by achiu             #+#    #+#             */
/*   Updated: 2024/08/01 12:36:01 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", STDOUT_FILENO);
		printf("%d\n", SIGQUIT);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	disable_ctrl_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	sig_init(void)
{
	// disable_ctrl_echo();
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}

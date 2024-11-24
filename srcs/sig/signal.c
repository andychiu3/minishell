/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:35:44 by achiu             #+#    #+#             */
/*   Updated: 2024/11/24 10:28:26 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// replace_line does not exist in libedit of ARM struct macOS
// rl_on_new_line and rl_redisplay behave differently?
void	sig_int(int sig)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig_num = sig;
}

void	sig_parse_heredoc(int sig)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	g_sig_num = sig;
}

void	sig_non_interactive(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

// TCSAFLUSH, TCSANOW and TCSADRAIN
void	disable_ctrl_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// void	sig_mode(int mode)
// {
// 	struct sigaction	act;

// 	ft_memset(&act, 0, sizeof(act));
// 	if (mode == INTERACTIVE)
// 	{
// 		act.sa_handler = sig_int;
// 		sigaction(SIGINT, &act, NULL);
// 		act.sa_handler = SIG_IGN;
// 		sigaction(SIGQUIT, &act, NULL);
// 	}
// 	else if (mode == PARSE)
// 	{
// 		act.sa_handler = sig_parse_heredoc;
// 		sigaction(SIGINT, &act, NULL);
// 	}
// 	else if (mode == NON_INTERACTIVE)
// 	{
// 		act.sa_handler = sig_non_interactive;
// 		sigaction(SIGINT, &act, NULL);
// 		sigaction(SIGQUIT, &act, NULL);
// 	}
// 	else if (mode == IN_CHILD)
// 	{
// 		act.sa_handler = SIG_DFL;
// 		sigaction(SIGINT, &act, NULL);
// 		sigaction(SIGQUIT, &act, NULL);
// 	}
// }

void	sig_mode(int mode)
{
	if (mode == INTERACTIVE)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == PARSE)
		signal(SIGINT, sig_parse_heredoc);
	else if (mode == NON_INTERACTIVE)
	{
		signal(SIGINT, sig_non_interactive);
		signal(SIGQUIT, sig_non_interactive);
	}
	else if (mode == IN_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

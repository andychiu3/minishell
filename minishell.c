/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:53:02 by achiu             #+#    #+#             */
/*   Updated: 2024/09/04 21:29:53 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prnt_token(token);
// prnt_ast(root, 0);
void	scanning(t_sh *sh, char *line)
{
	t_list	*token;
	t_ast	*root;

	if (!line)
		return ;
	if (!quote_case(line))
	{
		printf("unclosed quotes\n");
		return ;
	}
	token = NULL;
	lexer(line, &token, sh);
	// prnt_token(token);
	root = NULL;
	root = parser(&token);
	// prnt_ast(root, 0);
	exec_ast(root, 0, 1, sh);
	ft_out(token, root);
}

void	minishell(t_sh *sh)
{
	char	*line;

	while (1)
	{
		sig_init();
		line = readline(PROMPT);
		if (!line)
		{
			// printf("\033[1A\033[0K");
			// printf(PROMPT);
			// printf("\n");
			// disable_ctrl_echo();
			printf("exit\n");
			exit(0);
		}
		signal(SIGQUIT, sig_quit);
		if (*line)
			add_history(line);
		if (strcmp(line, "exit") == 0)
			exit(EXIT_SUCCESS);
		scanning(sh, line);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_sh	sh;

	(void) ac;
	(void) av;
	ft_memset(&sh, 0, sizeof(t_sh));
	// g_last_exit_code = 0;
	init_env(&sh, env);
	minishell(&sh);
	ft_freematrix(sh.env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <achiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:53:02 by achiu             #+#    #+#             */
/*   Updated: 2024/09/12 18:46:12 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*errormsg_exitcode(char *why, int exit_code, char *str)
{
	printf("why: %s\n", why);
	if (ft_strcmp(why, "syntax") == 0)
	{
		printf("minishell: syntax error near unexpected token");
		if (str)
			printf(" `%s'\n", str);
		else
			printf("`newline'\n");
	}
	else if (ft_strcmp(why, "nocmd") == 0)
		printf("minishell %s: command not found\n", str);
	else if (ft_strcmp(why, "EOF") == 0)
	{
		printf("minishell: unexpected EOF while looking for matching `%s'\n",
			str);
		printf("minishell: syntax error: unexpected end of file\n");
	}
	else if (ft_strcmp(why, "id") == 0)
		printf("minishell: export: '%s': not a valid identifier\n", str);
	g_last_exit_code = exit_code;
	return (NULL);
}

void	exec_ast(t_ast *root, int in_fd, int out_fd, t_sh *sh)
{
	if (!root)
		return ;
	if (root->type == PIPE)
		exec_pipe(root, in_fd, out_fd, sh);
	else if (is_redirect(root->type))
		process_redir(root, &in_fd, &out_fd, sh);
	else if (root->type == CMD)
		exec_cmd(root, in_fd, out_fd, sh);
}

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
	exec_ast(root, STDIN_FILENO, STDOUT_FILENO, sh);
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
		if (line && *line)
			add_history(line);
		scanning(sh, line);
		free(line);
	}
	// rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_sh	sh;

	(void) ac;
	(void) av;
	ft_memset(&sh, 0, sizeof(t_sh));
	g_last_exit_code = 0;
	init_env(&sh, env);
	minishell(&sh);
	ft_freematrix(sh.env);
	// malloc_printf("Leaked memory: %zu bytes\n", malloc_size(0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:53:02 by achiu             #+#    #+#             */
/*   Updated: 2024/11/20 21:26:46 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ast(t_ast *root, int in_fd, int out_fd, t_sh *sh)
{
	if (!root)
		return ;
	if (root->type == PIPE)
		exec_pipe(root, in_fd, out_fd, sh);
	else if (is_redirect(root->type))
		redir(root, &in_fd, &out_fd, sh);
	else if (root->type == CMD)
		exec_cmd(root, &in_fd, &out_fd, sh);
}

// prnt_token(token);
// prnt_ast(root, 0);
void	scanning(t_sh *sh, char *line)
{
	t_list	*token;
	t_ast	*root;
	t_list	*token_h;
	int		syntax_err;

	syntax_err = 0;
	if (!line || !quote_valid(line, sh))
		return ;
	token = NULL;
	lexer(line, &token);
	root = NULL;
	token_h = token;
	sig_mode(PARSE);
	root = parser(&token, &syntax_err, sh);
	if (g_sig_num == 2)
	{
		g_sig_num = 0;
		*(sh->ret) = 130;
	}
	sig_mode(NON_INTERACTIVE);
	if (!syntax_err && !sh->signaled)
		exec_ast(root, STDIN_FILENO, STDOUT_FILENO, sh);
	else
		syntax_err_case(syntax_err, token, sh);
	ft_out(token_h, root);
}

/*
support three entries:
1. ./minishell -c <CMD>
2. echo -e "<CMD>" | ./minishell without showing readline prompt
3. and of course interactive mode.
*/
char	*get_line(char *prompt, int ac, char **av, t_sh *sh)
{
	char	*line;
	char	*tmp;

	line = NULL;
	if (ac >= 2)
	{
		av++;
		if (validate_option(*av, 'c') == 1)
		{
			while (validate_option(*av, 'c') == 1)
				av++;
			line = ft_strdup(*av);
		}
		else
			return (redir_err(*av, 0, sh), exit(127), NULL);
	}
	else if (isatty(STDIN_FILENO))
		line = readline(prompt);
	else
	{
		tmp = get_next_line(STDIN_FILENO);
		line = ft_strtrim(tmp, "\n");
		free(tmp);
	}
	return (line);
}

void	minishell(t_sh *sh, int ac, char **av)
{
	char	*line;

	while (1)
	{
		init_flags(sh);
		sig_mode(INTERACTIVE);
		line = get_line(PROMPT, ac, av, sh);
		if (!line)
			end_of_file(ac, sh);
		if (line && *line)
			add_history(line);
		scanning(sh, line);
		free(line);
		if (ac >= 2)
			break ;
	}
	rl_clear_history();
}

// malloc_printf("Leaked memory: %zu bytes\n", malloc_size(0));
// disable_ctrl_echo();
int	main(int ac, char **av, char **env)
{
	t_sh	sh;

	ft_memset(&sh, 0, sizeof(t_sh));
	sh.ret = malloc(sizeof(int));
	if (!sh.ret)
		return (0);
	*(sh.ret) = 0;
	g_sig_num = 0;
	init_env(&sh, env);
	minishell(&sh, ac, av);
	ft_freematrix(&sh.env);
	free(sh.ret);
}

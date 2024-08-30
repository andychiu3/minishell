/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:53:02 by achiu             #+#    #+#             */
/*   Updated: 2024/08/29 11:17:13 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_env_value(t_sh *sh, char *target)
// {
// 	int		i;
// 	size_t	len;

// 	len = ft_strlen(target);
// 	i = -1;
// 	while (sh->env[++i])
// 		if (ft_strncmp(target, sh->env[i], len) == 0 && sh->env[i][len] == '=')
// 			return (ft_strchr(sh->env[i], '=') + 1);
// 	return (NULL);
// }

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
	lexer(line, &token);
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
			printf("\033[1A\033[0K");
			printf(PROMPT);
			printf("exit\n");
			exit(0);
		}
		signal(SIGQUIT, sig_quit);
		if (*line)
			add_history(line);
		scanning(sh, line);
	}
}

// STRDUP needed if we r gonna change/use env
// int	init_env(t_sh *sh, char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	sh->env = malloc(sizeof(char *) * (i + 1));
// 	if (!sh->env)
// 		return (0);
// 	i = -1;
// 	while (env[++i])
// 		sh->env[i] = ft_strdup(env[i]);
// 	return (1);
// }

int	main(int ac, char **av, char **env)
{
	t_sh	sh;

	(void) ac;
	(void) av;
	ft_memset(&sh, 0, sizeof(t_sh));
	init_env(&sh, env);
	minishell(&sh);
	ft_freematrix(sh.env);
}

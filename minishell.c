/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:53:02 by achiu             #+#    #+#             */
/*   Updated: 2024/07/30 10:53:05 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_sh *sh, char *target)
{
	int		i;
	size_t	len;

	len = ft_strlen(target);
	i = -1;
	while (sh->env[++i])
		if (ft_strncmp(target, sh->env[i], len) == 0 && sh->env[i][len] == '=')
			return (ft_strchr(sh->env[i], '=') + 1);
	return (NULL);
}

void	minishell(t_sh *sh)
{
	char	*line;

	(void) sh;
	while (1)
	{
		sig_init();
		line = readline(PROMPT);
		if (!line)
		{
			rl_redisplay();
			ft_putstr_fd(" exit", STDOUT_FILENO);
			exit(0);
		}
		signal(SIGQUIT, sig_quit);
		if (*line)
			add_history(line);
		// check_line(line);
		// tokenize(line);
		// parse();
		// free(line);
	}
}

// STRDUP needed if we r gonna change/use env
int	init_env(t_sh *sh, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	sh->env = malloc(sizeof(char *) * (i + 1));
	if (!sh->env)
		return (0);
	i = -1;
	while (env[++i])
		sh->env[i] = ft_strdup(env[i]);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_sh	sh;

	(void) ac;
	(void) av;
	ft_memset(&sh, 0, sizeof(t_sh));
	init_env(&sh, env);
	minishell(&sh);
}

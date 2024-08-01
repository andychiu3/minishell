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

/*
sgl quote
dbl quote
skip space

*/
// int	check_av()
// {

// }

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
		line = readline(PROMPT);
		if (!line)
		{
			// rl_replace_line("", 0);
        	// rl_on_new_line();
       		// rl_redisplay();
			write(1, "exit", 4);
			break ;
		}
		// signal(SIGINT, sig_handler);
		// signal(SIGQUIT, sig_handler);
		// if (*line)
		// 	add_history(line);
		// check_line(line);
		// tokenize(line);
		// parse();
		//  free(line);
	}
}

// STRDUP needed if we r gonna change/use env
int	init_(t_sh *sh, char **env)
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
	// int		i;

	(void) ac;
	(void) av;
	ft_memset(&sh, 0, sizeof(t_sh));
	//check_av();
	init_(&sh, env);
	minishell(&sh);
	// i = -1;
	// while (sh.env[++i])
	// 	printf("%s\n", sh.env[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:31:55 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/21 18:38:55 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_n_exit(char *input, char *dlmtr, int exit_code)
{
	if (input)
		free(input);
	if (dlmtr)
		free(dlmtr);
	exit(exit_code);
}

void	end_of_file(int ac, t_sh *sh)
{
	int	tmp;

	if (ac >= 2)
	{
		err_printf("minishell: -c: option requires an argument\n");
		*(sh->ret) = 2;
	}
	else if (isatty(STDIN_FILENO))
	{
		printf("\033[1A\033[0K");
		printf(PROMPT);
		printf("exit\n");
	}
	ft_freematrix(&sh->env);
	tmp = *(sh->ret);
	free(sh->ret);
	exit(tmp);
}

void	function_err_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

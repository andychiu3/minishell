/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:02:58 by achiu             #+#    #+#             */
/*   Updated: 2024/10/19 21:15:08 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	waitpid_status(int *status, t_sh *sh)
{
	int	sig;

	if (WIFEXITED(*status))
		*(sh->ret) = WEXITSTATUS(*status);
	if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		if (sig == SIGINT)
			*(sh->ret) = 128 + sig;
		else if (sig == SIGQUIT)
			*(sh->ret) = 128 + sig;
	}
	return (1);
}

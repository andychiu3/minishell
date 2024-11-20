/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:05:28 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/11 09:05:32 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_flags(t_sh *sh)
{
	if (!sh)
		return ;
	sh->signaled = 0;
	sh->pipe_in = 0;
	sh->pipe_out = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:03:54 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 12:22:20 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prnt_syntax_err(char *str)
{
	err_printf("minishell: syntax error near unexpected token ");
	if (str)
		err_printf("`%s'\n", str);
	else
		ft_putendl_fd("`newline'", STDERR_FILENO);
}

void	prnt_eof_err(char *str)
{
	err_printf("minishell: unexpected EOF while looking for matching `%s'\n",
		str);
	err_printf("minishell: syntax error: unexpected end of file\n");
}

char	*errormsg_exitcode(char *why, int exit_code, char *str, t_sh *sh)
{
	if (ft_strcmp(why, "syntax") == 0)
		prnt_syntax_err(str);
	else if (ft_strcmp(why, "nocmd") == 0)
		err_printf("minishell: %s: command not found\n", str);
	else if (ft_strcmp(why, "EOF") == 0)
		prnt_eof_err(str);
	*(sh->ret) = exit_code;
	return (NULL);
}

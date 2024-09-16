/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:03:54 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/16 16:49:10 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prnt_syntax_err(char *str)
{
	err_printf("minishell: syntax error near unexpected token ");
	if (str)
		err_printf("`str'\n", str);
	else
		ft_putendl_fd("`newline'", STDERR_FILENO);
}

void	prnt_eof_err(char *str)
{
	err_printf("minishell: unexpected EOF while looking for matching `%s'\n",
		str);
	err_printf("minishell: syntax error: unexpected end of file\n");
}

void	prnt_cd_err(char *why, char *str)
{
	if (ft_strcmp("cd: invalid", why) == 0)
		err_printf("minishell: cd: %s: No such file or directory\n", str);
	else if (ft_strcmp("cd: notdir", why) == 0)
		err_printf("minishell: cd: %s: Not a directory\n", str);
	else if (ft_strcmp("cd: cantx", why) == 0)
		err_printf("minishell: cd: %s: Permission denied\n", str);
	else if (ft_strcmp("cd: 2arg", why) == 0)
		err_printf("minishell: cd: too many arguments\n");
}

void	prnt_env_err(char *cmd, char *arg)
{
	if (ft_strcmp("=", arg) == 0)
		err_printf("%s: setenv %s: Invalid argument\n", cmd, arg);
	else if (ft_strncmp("-", arg, 1) == 0)
	{
		err_printf("%s: illegal option -- %c\n", cmd, arg[1]);
		err_printf("usage: env [-0iv] [-P utilpath] [-S string] [-u name]\n");
		err_printf("           [name=value ...] [utility [argument ...]]\n");
	}
	else
		err_printf("%s: %s: No such file or directory\n", cmd, arg);
}

char	*errormsg_exitcode(char *why, int exit_code, char *str)
{
	if (ft_strcmp(why, "syntax") == 0)
		prnt_syntax_err(str);
	else if (ft_strcmp(why, "nocmd") == 0)
		err_printf("minishell: %s: command not found\n", str);
	else if (ft_strcmp(why, "EOF") == 0)
		prnt_eof_err(str);
	else if (ft_strcmp(why, "export") == 0 || ft_strcmp(why, "unset") == 0)
		err_printf("minishell: %s: `%s': not a valid identifier\n", why, str);
	else if (ft_strcmp(why, "env") == 0)
		prnt_env_err(why, str);
	else if (ft_strncmp(why, "cd: ", 4) == 0)
		prnt_cd_err(why, str);
	g_last_exit_code = exit_code;
	return (NULL);
}

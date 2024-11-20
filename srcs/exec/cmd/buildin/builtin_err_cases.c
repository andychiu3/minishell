/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_err_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:18:52 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 12:13:26 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prnt_export_err(char *why, char *str)
{
	if (ft_strcmp("export: invalid", why) == 0)
		err_printf("minishell: export: %s: not a valid identifier\n", str);
	else if (ft_strcmp("export: option", why) == 0)
	{
		err_printf("minishell: export: %s: invalid option\n", str);
		err_printf("export: usage: export [-nf] ");
		err_printf("[name[=value] ...] or export -p\n");
	}
}

void	prnt_unset_err(char *why, char *str)
{
	if (ft_strcmp("unset: invalid", why) == 0)
		err_printf("minishell: unset: %s: not a valid identifier\n", str);
	else if (ft_strcmp("unset: option", why) == 0)
	{
		err_printf("minishell: unset: %s: invalid option\n", str);
		err_printf("unset: usage: unset [-f] [-v] [name ...]\n");
	}
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
	else if (ft_strcmp("cd: oldpwd", why) == 0)
		err_printf("minishell: cd: OLDPWD not set\n");
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

char	*builtin_err_cases(char *why, int exit_code, char *str, t_sh *sh)
{
	if (ft_strncmp(why, "export", 6) == 0)
		prnt_export_err(why, str);
	else if (ft_strncmp(why, "unset", 5) == 0)
		prnt_unset_err(why, str);
	else if (ft_strcmp(why, "env") == 0)
		prnt_env_err(why, str);
	else if (ft_strncmp(why, "cd: ", 4) == 0)
		prnt_cd_err(why, str);
	*(sh->ret) = exit_code;
	return (NULL);
}

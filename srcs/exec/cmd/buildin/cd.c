/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:29:18 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 13:28:31 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updateoldpwd_chdir(char *target_path, t_sh *sh)
{
	char	*path;

	path = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	exec_export(path, sh);
	free(path);
	chdir(target_path);
	path = ft_strjoin("PWD=", getcwd(NULL, 0));
	exec_export(path, sh);
}

// - OLDPWD
// no arg HOME
char	*wd_cases(t_cmd *cmd, t_sh *sh)
{
	char	*target_path;

	target_path = NULL;
	if (!cmd->arg)
		target_path = ft_strdup(getenv("HOME"));
	else if (ft_strcmp(cmd->arg[0], "-") == 0)
	{
		target_path = ft_strdup(get_env_value(sh, "OLDPWD"));
		if (target_path)
			printf("%s\n", target_path);
		else
			builtin_err_cases("cd: oldpwd", 1, target_path, sh);
	}
	return (target_path);
}

void	exec_cd(char *path, t_sh *sh)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (ft_strcmp(path, "-") == 0)
		return ;
	else if (access(path, F_OK) == -1)
		builtin_err_cases("cd: invalid", 1, path, sh);
	else if (!S_ISDIR(path_stat.st_mode))
		builtin_err_cases("cd: notdir", 1, path, sh);
	else if (access(path, X_OK) == -1)
		builtin_err_cases("cd: cantx", 1, path, sh);
	else if (access(path, F_OK | X_OK) == 0)
	{
		updateoldpwd_chdir(path, sh);
		*(sh->ret) = 0;
	}
}

void	process_cd(t_cmd *cmd, t_sh *sh)
{
	char	*path;

	path = NULL;
	if (!cmd || !sh)
		return ;
	if (ft_strs_count(cmd->arg) == 0 || ft_strs_count(cmd->arg) == 1)
	{
		path = wd_cases(cmd, sh);
		if (path)
		{
			exec_cd(path, sh);
			free(path);
		}
		else if (cmd->arg)
			exec_cd(*cmd->arg, sh);
	}
	else
		builtin_err_cases("cd: 2arg", 1, path, sh);
}

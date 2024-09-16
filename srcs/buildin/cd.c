/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:29:18 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/16 15:12:33 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updateoldpwd_chdir(char *target_path, t_sh *sh)
{
	char	*path;

	path = ft_strjoin("OLDPWD=", get_env_value(sh, "PWD"));
	exec_export(path, sh);
	free(path);
	chdir(target_path);
	path = ft_strjoin("PWD=", getcwd(NULL, 0));
	exec_export(path, sh);
}

char	*expand_path(t_cmd *cmd, t_sh *sh)
{
	char	*target_path;
	char	*pwd;

	target_path = NULL;
	pwd = get_env_value(sh, "PWD");
	if (ft_strncmp("./", cmd->arg[0], 2) == 0)
		target_path = ft_strdup(pwd);
	else if (ft_strncmp("~/", cmd->arg[0], 2) == 0)
		target_path = ft_strdup(getenv("HOME"));
	else if (ft_strncmp("../", cmd->arg[0], 3) == 0)
		target_path = ft_substr(pwd, 0, ft_strrchr(pwd, '/') - pwd);
	if (cmd->arg && *cmd->arg && (ft_strchr(*cmd->arg, '/') + 1))
		target_path = ft_strjoin(target_path, (ft_strchr(*cmd->arg, '/')));
	return (target_path);
}

// . and ./ current
// ~ and ~/ HOME
// - OLDPWD
// no arg HOME
char	*wd_cases(t_cmd *cmd, t_sh *sh)
{
	char	*target_path;

	target_path = NULL;
	if (!cmd->arg || ft_strcmp("~", cmd->arg[0]) == 0)
		target_path = ft_strdup(getenv("HOME"));
	else if (ft_strcmp(cmd->arg[0], "..") == 0
		|| ft_strcmp(cmd->arg[0], ".") == 0)
		target_path = ft_strdup(cmd->arg[0]);
	else if (ft_strcmp(cmd->arg[0], "-") == 0)
		target_path = ft_strdup(get_env_value(sh, "OLDPWD"));
	else if (ft_strncmp("~/", cmd->arg[0], 2) == 0
		|| ft_strncmp("./", cmd->arg[0], 2) == 0
		|| ft_strncmp("../", cmd->arg[0], 3) == 0)
		target_path = expand_path(cmd, sh);
	return (target_path);
}

// int	valid_arg_amount(t_cmd *cmd)
// {
// 	if (!cmd)
// 		return (0);
// 	return (ft_strs_count(cmd->arg) == 0 || ft_strs_count(cmd->arg) == 1);
// }

void	exec_cd(char *path, t_sh *sh)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (access(path, F_OK) == -1)
		err_printf("minishell: cd: %s: No such file or directory\n", path);
	else if (!S_ISDIR(path_stat.st_mode))
		err_printf("minishell: cd: %s: Not a directory\n", path);
	else if (access(path, X_OK) == -1)
		err_printf("minishell: cd: %s: Permission denied\n", path);
	else if (access(path, F_OK | X_OK) == 0)
		updateoldpwd_chdir(path, sh);
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
		else
			exec_cd(*cmd->arg, sh);
	}
	else
		err_printf("minishell: cd: too many arguments\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:29:18 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/31 14:08:40 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updateoldpwd_chdir(char *target_path, t_sh *sh)
{
	char	*path;

	path = ft_strjoin("OLDPWD=", get_env_value(sh, "PWD"));
	exec_export(path, sh);
	free(path);
	// printf("target path: %s\n", target_path);
	chdir(target_path);
	path = ft_strjoin("PWD=", getcwd(NULL, 0));
	exec_export(path, sh);
}

char	*expand_path(t_cmd *cmd, t_sh *sh)
{
	char	*target_path;

	target_path = NULL;
	if (strncmp("./", cmd->arg[0], 2) == 0)
		target_path = ft_strdup(get_env_value(sh, "PWD"));
	else if (strncmp("~/", cmd->arg[0], 2) == 0)
		target_path = ft_strdup(getenv("HOME"));
	else if (strncmp("../", cmd->arg[0], 3) == 0)
		target_path = ft_strdup(getenv("HOME"));
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
	if (!cmd->arg || strcmp("~", cmd->arg[0]) == 0)
		target_path = ft_strdup(getenv("HOME"));
	else if (ft_strcmp(cmd->arg[0], "..") == 0
		|| ft_strcmp(cmd->arg[0], ".") == 0)
		target_path = ft_strdup(cmd->arg[0]);
	else if (ft_strcmp(cmd->arg[0], "-") == 0)
		target_path = ft_strdup(get_env_value(sh, "OLDPWD"));
	else if (strncmp("~/", cmd->arg[0], 2) == 0
		|| strncmp("./", cmd->arg[0], 2) == 0
		|| strncmp("../", cmd->arg[0], 3) == 0)
		target_path = expand_path(cmd, sh);
	return (target_path);
}

int	valid_arg_amount(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strs_count(cmd->arg) == 0 || ft_strs_count(cmd->arg) == 1);
}

void	process_cd(t_cmd *cmd, t_sh *sh)
{
	char	*path;

	path = NULL;
	if (!cmd || !sh)
		return ;
	if (valid_arg_amount(cmd))
	{
		path = wd_cases(cmd, sh);
		// printf("path: %s\n", path);
		if (path && access(path, F_OK | X_OK) == 0)
			updateoldpwd_chdir(path, sh);
		else if (access(*cmd->arg, F_OK | X_OK) == 0)
			updateoldpwd_chdir(*cmd->arg, sh);
		else if (!path)
			printf("minishell: cd: %s: No such file or directory\n", *cmd->arg);
		else
			printf("minishell: cd: %s: No such file or directory\n", path);
		free(path);
	}
	else
		printf("minishell: cd: too many arguments\n");
}

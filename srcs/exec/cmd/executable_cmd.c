/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:10:31 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 13:23:56 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*execve_case(char *why, char *str, int exit_code, t_sh *sh)
{
	*(sh->ret) = exit_code;
	if (ft_strcmp(".", why) == 0)
	{
		err_printf("minishell: %s: filename argument required\n", str);
		err_printf(".: usage: . filename [arguments]\n");
	}
	else if (ft_strcmp("invalid", why) == 0)
		err_printf("minishell: %s: No such file or directory\n", str);
	else if (ft_strcmp("dir", why) == 0)
		err_printf("minishell: %s: Is a directory\n", str);
	else if (ft_strcmp("cantx", why) == 0)
		err_printf("minishell: %s: Permission denied\n", str);
	return (NULL);
}

char	*does_path_exist(char *str, t_sh *sh)
{
	char	*full_path;
	char	**path_split;
	int		i;
	char	*tmp;

	path_split = ft_split(get_env_value(sh, "PATH"), ':');
	i = -1;
	while (path_split && path_split[++i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		full_path = ft_strjoin(tmp, str);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_freematrix(&path_split);
			return (full_path);
		}
		free(full_path);
	}
	ft_freematrix(&path_split);
	return (NULL);
}

char	*not_executable(char *str, t_sh *sh)
{
	struct stat	path_stat;

	if (!str)
		return (NULL);
	stat(str, &path_stat);
	if (ft_strcmp(".", str) == 0)
		return (execve_case(".", str, 127, sh));
	else if (ft_strcmp("..", str) == 0)
		return (errormsg_exitcode("nocmd", 127, str, sh));
	else if (ft_strchr(str, '/'))
	{
		if (access(str, F_OK) == -1)
			return (execve_case("invalid", str, 127, sh));
		else if (access(str, X_OK) == -1)
			return (execve_case("cantx", str, 126, sh));
		else if (S_ISDIR(path_stat.st_mode))
			return (execve_case("dir", str, 126, sh));
		else
			return (errormsg_exitcode("nocmd", 127, str, sh));
	}
	else
		return (errormsg_exitcode("nocmd", 127, str, sh));
}

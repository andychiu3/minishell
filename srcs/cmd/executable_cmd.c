/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:10:31 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/11 11:19:41 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*does_path_exist(char *str, t_sh *sh)
{
	char	*full_path;
	char	**path_split;
	int		i;
	char	*tmp;

	path_split = ft_split(get_env_value(sh, "PATH"), ':');
	i = -1;
	while (path_split[++i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		full_path = ft_strjoin(tmp, str);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_freematrix(path_split);
			return (full_path);
		}
		free(full_path);
	}
	ft_freematrix(path_split);
	return (NULL);
}

char	*is_executable(char *str, t_sh *sh)
{
	if (!str || !*str)
		return (NULL);
	if (ft_strchr(str, '/'))
	{
		if (access(str, F_OK | X_OK) == 0)
			return (ft_strdup(str));
		else
			return (NULL);
	}
	else
		return (does_path_exist(str, sh));
}

// char	*is_executable(char *str, t_sh *sh)
// {
// 	char	*full_path;
// 	char	**path_split;
// 	int		i;
// 	char	*tmp;

// 	if (!str || !*str)
// 		return (NULL);
// 	if (ft_strchr(str, '/'))
// 	{
// 		if (access(str, F_OK | X_OK) == 0)
// 			return (ft_strdup(str));
// 	}
// 	else
// 	{
// 		path_split = ft_split(get_env_value(sh, "PATH"), ':');
// 		i = -1;
// 		while (path_split[++i])
// 		{
// 			tmp = ft_strjoin(path_split[i], "/");
// 			full_path = ft_strjoin(tmp, str);
// 			free(tmp);
// 			if (access(full_path, F_OK | X_OK) == 0)
// 			{
// 				ft_freematrix(path_split);
// 				return (full_path);
// 			}
// 			free(full_path);
// 		}
// 		ft_freematrix(path_split);
// 	}
// 	return (NULL);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:58:35 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/02 11:41:48 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**combine_cmd_arg_with_path(t_cmd *cmd, char *path)
{
	char	**new;
	int		i;

	if (!cmd)
		return (NULL);
	if (!cmd->arg)
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_strjoin(path, cmd->cmd);
		new[1] = NULL;
		return (new);
	}
	new = malloc(sizeof(char *) * (ft_strs_count(cmd->arg) + 2));
	if (!new)
		return (NULL);
	new[0] = ft_strjoin(path, cmd->cmd);
	i = 1;
	while (*cmd->arg)
		new[i++] = ft_strdup(*cmd->arg++);
	new[i] = NULL;
	return (new);
}

void	exec_with_execve(t_cmd *cmd, t_sh *sh)
{
	char	**arg;

	if (!cmd || !sh)
		return ;
	if (ft_strcmp(cmd->cmd, "ls") == 0
		|| ft_strcmp(cmd->cmd, "cat") == 0)
		arg = combine_cmd_arg_with_path(cmd, "/bin/");
	else
		arg = combine_cmd_arg_with_path(cmd, "/usr/bin/");
	if (ft_strcmp(cmd->cmd, "ls") == 0)
		execve("/bin/ls", arg, sh->env);
	else if (ft_strcmp(cmd->cmd, "clear") == 0)
		execve("/usr/bin/clear", arg, sh->env);
	else if (ft_strcmp(cmd->cmd, "grep") == 0)
		execve("/usr/bin/grep", arg, sh->env);
	else if (ft_strcmp(cmd->cmd, "cat") == 0)
		execve("/bin/cat", arg, sh->env);
	ft_freematrix(arg);
}

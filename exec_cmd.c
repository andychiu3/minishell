/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:01:48 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/30 10:34:50 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_cmd *cmd, int in_fd, int out_fd)
{
	int	i;
	int	nextline;

	if (!cmd)
		return ;
	(void)in_fd;
	nextline = 1;
	i = 0;
	if (strncmp("-n", cmd->arg[i], ft_strlen(cmd->arg[i])) == 0)
	{
		nextline = 0;
		i++;
	}
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], out_fd);
		if (cmd->arg[i + 1])
			ft_putchar_fd(' ', out_fd);
		i++;
	}
	if (nextline)
		ft_putchar_fd('\n', out_fd);
}

void	exec_pwd(t_cmd *cmd, int in_fd, int out_fd)
{
	char	*pwd;

	if (!cmd)
		return ;
	(void)in_fd;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, out_fd);
		free (pwd);
	}
}

void	exec_env(t_cmd *cmd, int in_fd, int out_fd, t_sh *sh)
{
	int	i;

	if (!cmd)
		return ;
	(void)in_fd;
	i = -1;
	while (sh->env[++i])
		ft_putendl_fd(sh->env[i], out_fd);
}

void	exec_cmd(t_ast *root, int in_fd, int out_fd, t_sh *sh)
{
	t_cmd	*cmd;

	if (!root)
		return ;
	(void)in_fd;
	cmd = (t_cmd *)root->content;
	if (strncmp(cmd->cmd, "echo", ft_strlen(cmd->cmd)) == 0)
		exec_echo(cmd, in_fd, out_fd);
	else if (strncmp(cmd->cmd, "pwd", ft_strlen(cmd->cmd)) == 0)
		exec_pwd(cmd, in_fd, out_fd);
	else if (strncmp(cmd->cmd, "env", ft_strlen(cmd->cmd)) == 0)
		exec_env(cmd, in_fd, out_fd, sh);
	else if (strncmp(cmd->cmd, "export", ft_strlen(cmd->cmd)) == 0)
		process_export(cmd, sh);
	else if (strncmp(cmd->cmd, "unset", ft_strlen(cmd->cmd)) == 0)
		process_unset(cmd, sh);
	else if (strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)) == 0)
		process_cd(cmd, sh);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:01:48 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/10 21:41:05 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_cmd *cmd, int in_fd, int out_fd)
{
	int	i;
	int	nextline;

	if (!cmd || !cmd->arg)
		return ;
	(void)in_fd;
	nextline = 1;
	i = 0;
	if (strcmp("-n", cmd->arg[i]) == 0)
	{
		nextline = 0;
		i++;
	}
	while (cmd->arg[i])
	{
		if (cmd->arg[i])
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
	(void)out_fd;
	i = -1;
	if (cmd->arg)
	{
		printf("minishell: cd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	while (sh->env[++i])
		ft_putendl_fd(sh->env[i], STDOUT_FILENO);
}

void	exec_exit(t_cmd *cmd)
{
	int	exit_nbr;

	if (!cmd)
		return ;
	exit_nbr = 0;
	if (cmd->arg)
	{
		if (ft_isnbr(cmd->arg[0]))
			exit_nbr = ft_atoi(cmd->arg[0]);
		else
		{
			ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
			ft_putstr_fd(cmd->arg[0], STDOUT_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
			exit_nbr = 1;
			exit(exit_nbr % 256);
		}
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->arg && cmd->arg[1])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDOUT_FILENO);
		exit_nbr = 1;
	}
	exit(exit_nbr % 256);
}

void	exec_cmd(t_ast *root, int in_fd, int out_fd, t_sh *sh)
{
	t_cmd	*cmd;

	if (!root)
		return ;
	(void)in_fd;
	cmd = (t_cmd *)root->content;
	if (strcmp(cmd->cmd, "echo") == 0)
		exec_echo(cmd, in_fd, out_fd);
	else if (strcmp(cmd->cmd, "pwd") == 0)
		exec_pwd(cmd, in_fd, out_fd);
	else if (strcmp(cmd->cmd, "env") == 0)
		exec_env(cmd, in_fd, out_fd, sh);
	else if (strcmp(cmd->cmd, "export") == 0)
		process_export(cmd, sh);
	else if (strcmp(cmd->cmd, "unset") == 0)
		process_unset(cmd, sh);
	else if (strcmp(cmd->cmd, "cd") == 0)
		process_cd(cmd, sh);
	else if (strcmp(cmd->cmd, "exit") == 0)
		exec_exit(cmd);
	else if (is_executable(cmd->cmd, sh))
		exec_with_execve(cmd, sh);
	// else
	// {
	// 	printf("hi\n");
	// 	errormsg_exitcode("nocmd", 1, cmd->cmd);
	// 	exit (1);
	// }
}

// else if (strcmp(cmd->cmd, "ls") == 0
// 		|| strcmp(cmd->cmd, "clear") == 0
// 		|| strcmp(cmd->cmd, "grep") == 0
// 		|| strcmp(cmd->cmd, "cat") == 0)
// 		exec_with_execve(cmd, sh);
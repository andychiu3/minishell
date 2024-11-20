/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:58:35 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 21:13:45 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_arg_for_execve(t_cmd *cmd, char *path)
{
	char	**arg;
	int		i;

	if (!cmd)
		return (NULL);
	arg = NULL;
	if (path)
		add_str_to_strs(&arg, path);
	else if (cmd->cmd)
		add_str_to_strs(&arg, cmd->cmd);
	i = 0;
	while (cmd->arg && cmd->arg[i])
		add_str_to_strs(&arg, cmd->arg[i++]);
	return (arg);
}

void	exec_with_execve(t_cmd *cmd, t_sh *sh)
{
	char	**arg;
	char	*path;

	if (!cmd || !sh)
		return ;
	arg = NULL;
	path = NULL;
	if (!ft_strchr(cmd->cmd, '/'))
		path = does_path_exist(cmd->cmd, sh);
	arg = get_arg_for_execve(cmd, path);
	execve(arg[0], arg, sh->env);
	not_executable(cmd->cmd, sh);
	if (arg)
		ft_freematrix(&arg);
	exit(*(sh->ret));
}

void	fork_for_execve(t_ast *root, int *in_fd, int *out_fd, t_sh *sh)
{
	pid_t	pid;
	int		status;

	(void)in_fd;
	(void)out_fd;
	pid = fork();
	if (pid == 0)
	{
		sig_mode(IN_CHILD);
		redir_n_backup_std_io(in_fd, out_fd, NULL);
		exec_with_execve((t_cmd *)root->content, sh);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		if (sh->pipe_out)
			sig_mode(IN_CHILD);
		close_unuse_fd(in_fd, out_fd);
		waitpid(pid, &status, 0);
		waitpid_status(&status, sh);
	}
}

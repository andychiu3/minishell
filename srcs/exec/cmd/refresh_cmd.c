/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:17:32 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/10 09:50:18 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_cmd_element(char **element, char ***tmp, t_sh *sh)
{
	int		ambiguous;
	char	**split;
	int		i;

	expand_path(element);
	ambiguous = check_var(element, sh);
	if (!ambiguous)
	{
		split = lexer_for_var(*element);
		i = 0;
		while (split && split[i])
			add_str_to_strs(tmp, split[i++]);
		ft_freematrix(&split);
	}
}

// handle ~ and ~/
// var swap and handle amigious case
char	**store_in_tmp(t_cmd *cmd, t_sh *sh)
{
	int		i;
	char	**tmp;

	if (!cmd)
		return (NULL);
	tmp = NULL;
	if (cmd->cmd)
		process_cmd_element(&cmd->cmd, &tmp, sh);
	i = 0;
	while (cmd->arg && cmd->arg[i])
		process_cmd_element(&cmd->arg[i++], &tmp, sh);
	return (tmp);
}

void	clean_cmd_ptr(t_cmd *cmd)
{
	if (cmd->cmd)
	{
		free(cmd->cmd);
		cmd->cmd = NULL;
	}
	ft_freematrix(&cmd->arg);
}

void	update_cmd(t_cmd *cmd, char **cmd_in_matrix)
{
	int		i;

	if (!cmd || !cmd_in_matrix)
		return ;
	i = 0;
	if (cmd_in_matrix[i])
		cmd->cmd = ft_strdup(cmd_in_matrix[i++]);
	while (cmd_in_matrix[i])
		add_str_to_strs(&cmd->arg, cmd_in_matrix[i++]);
}

void	refresh_cmd(t_cmd *cmd, t_sh *sh)
{
	char	**tmp;

	if (!cmd)
		return ;
	tmp = NULL;
	tmp = store_in_tmp(cmd, sh);
	rm_strs_quote(tmp);
	clean_cmd_ptr(cmd);
	update_cmd(cmd, tmp);
	ft_freematrix(&tmp);
}

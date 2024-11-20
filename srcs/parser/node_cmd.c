/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:49:54 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/11 10:06:34 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_count(t_list *token)
{
	int	i;

	i = 0;
	while (token && !(is_op(((t_token *)((*token).content))->type)))
	{
		token = token->next;
		i++;
	}
	return (i);
}

// consider if ft_strdup fail?
void	cmd_node_has_arg(t_ast *cmd_node, t_list **token)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)cmd_node->content;
	cmd->arg = malloc((arg_count(*token) + 1) * sizeof(char *));
	if (!cmd->arg)
		function_err_exit("malloc error");
	i = 0;
	while (*token && !(is_op(((t_token *)((*token)->content))->type)))
	{
		cmd->arg[i++] = ft_strdup((((t_token *)((*token)->content))->content));
		*token = (*token)->next;
	}
	cmd->arg[i] = NULL;
}

t_ast	*create_cmd_node(t_list **tokens)
{
	t_ast	*cmd_node;

	cmd_node = malloc(sizeof(t_ast));
	if (!cmd_node)
		function_err_exit("malloc error");
	ft_memset(cmd_node, 0, sizeof(t_ast));
	cmd_node->type = CMD;
	cmd_node->content = malloc(sizeof(t_cmd));
	if (!cmd_node->content)
	{
		free(cmd_node);
		return (NULL);
	}
	ft_memset(cmd_node->content, 0, sizeof(t_cmd));
	((t_cmd *)(cmd_node->content))->cmd
		= ft_strdup(((t_token *)((*tokens)->content))->content);
	*tokens = (*tokens)->next;
	if (*tokens && !(is_op(((t_token *)((*tokens)->content))->type)))
		cmd_node_has_arg(cmd_node, tokens);
	return (cmd_node);
}

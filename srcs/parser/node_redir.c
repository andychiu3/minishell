/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:56:24 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/14 09:06:46 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_cmd_args(t_ast **node, t_list **token)
{
	t_cmd	*cmd;

	if (!*node)
	{
		*node = create_cmd_node(token);
	}
	else if (*node)
	{
		cmd = (t_cmd *)((*node)->content);
		while (*token && !is_op(((t_token *)(*token)->content)->type))
		{
			add_str_to_strs(&cmd->arg, ((t_token *)(*token)->content)->content);
			*token = (*token)->next;
		}
	}
}

// do redir need a file after?
t_redirect	*create_redir(t_list **token)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	ft_memset(redir, 0, sizeof(t_redirect));
	redir->redir = ft_strdup(((t_token *)(*token)->content)->content);
	*token = (*token)->next;
	if (token && *token && is_op(((t_token *)(*token)->content)->type))
		return (NULL);
	if (token && *token && (*token)->content)
	{
		redir->file = ft_strdup(((t_token *)(*token)->content)->content);
		*token = (*token)->next;
	}
	return (redir);
}

// if (!redir_node->right)
// 	return ((t_ast *)errormsg_exitcode("sytax", 258, NULL));
t_ast	*handle_redirect(t_ast *node, t_list **token, int call, t_ast *tmp)
{
	t_ast	*redir_node;

	redir_node = malloc(sizeof(t_ast));
	if (!redir_node)
		return (NULL);
	ft_memset(redir_node, 0, sizeof(t_ast));
	redir_node->type = ((t_token *)(*token)->content)->type;
	redir_node->content = create_redir(token);
	if (call && node && node->type == CMD)
	{
		redir_node->left = node;
		tmp = redir_node->left;
	}
	if (!redir_node->content || (node && node->type == ARG))
	{
		free (redir_node);
		return (NULL);
	}
	if (*token && !is_op(((t_token *)(*token)->content)->type))
	{
		if (tmp)
			append_cmd_args(&tmp, token);
		else
		{
			append_cmd_args(&redir_node->left, token);
			tmp = redir_node->left;
		}
	}
	if (*token && is_redirect(((t_token *)(*token)->content)->type))
		redir_node->right = handle_redirect(node, token, 0, tmp);
	return (redir_node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:17:26 by achiu             #+#    #+#             */
/*   Updated: 2024/11/20 21:13:49 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_cmd_args(t_ast **node, t_list **token)
{
	t_cmd	*cmd;

	if (!*node)
		*node = create_cmd_node(token);
	else
	{
		cmd = (t_cmd *)((*node)->content);
		while (*token && !is_op(((t_token *)(*token)->content)->type))
		{
			add_str_to_strs(&cmd->arg, ((t_token *)(*token)->content)->content);
			*token = (*token)->next;
		}
	}
}

t_redirect	*create_redir(t_list **token, int *syntax_err)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		function_err_exit("malloc error");
	ft_memset(redir, 0, sizeof(t_redirect));
	redir->heredoc_fd = -1;
	redir->redir = ft_strdup(((t_token *)(*token)->content)->content);
	*token = (*token)->next;
	if (token && *token && is_op(((t_token *)(*token)->content)->type))
		return (syntax_error(syntax_err, 3));
	if (token && *token && !is_op(((t_token *)(*token)->content)->type))
	{
		redir->file = ft_strdup(((t_token *)(*token)->content)->content);
		*token = (*token)->next;
	}
	if (!redir->file)
		return (syntax_error(syntax_err, 1));
	return (redir);
}

t_ast	*create_node_redir(t_list **token, int *syntax_err)
{
	t_ast	*redir_node;

	redir_node = malloc(sizeof(t_ast));
	if (!redir_node)
		function_err_exit("malloc error");
	ft_memset(redir_node, 0, sizeof(t_ast));
	redir_node->type = ((t_token *)(*token)->content)->type;
	redir_node->content = create_redir(token, syntax_err);
	if (!redir_node->content)
		return (NULL);
	return (redir_node);
}

t_ast	*handle_recur_redir(t_ast **node_r,
			t_list **token, int *syntax_err, t_sh *sh)
{
	t_ast	*redir_node;

	redir_node = create_node_redir(token, syntax_err);
	if (!redir_node)
		return (NULL);
	if (redir_node->type == HEREDOC && !sh->signaled)
		fork_for_heredoc((t_redirect *)redir_node->content, sh);
	if (*token && !is_op(((t_token *)(*token)->content)->type))
		append_cmd_args(node_r, token);
	if (*token && is_redirect(((t_token *)(*token)->content)->type))
		redir_node->left = handle_recur_redir(node_r, token, syntax_err, sh);
	return (redir_node);
}

// for parameter saving: handle_recur_redir
t_ast	*handle_init_redir(t_ast *node,
			t_list **token, int *syntax_err, t_sh *sh)
{
	t_ast	*redir_node;

	redir_node = create_node_redir(token, syntax_err);
	if (!redir_node)
		return (NULL);
	if (redir_node->type == HEREDOC)
		fork_for_heredoc((t_redirect *)redir_node->content, sh);
	if (node && node->type == CMD)
		redir_node->right = node;
	if (*token && !is_op(((t_token *)(*token)->content)->type))
		append_cmd_args(&redir_node->right, token);
	if (*token && is_redirect(((t_token *)(*token)->content)->type))
		redir_node->left
			= handle_recur_redir(&redir_node->right, token, syntax_err, sh);
	return (redir_node);
}

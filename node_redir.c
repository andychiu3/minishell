/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:56:24 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/26 16:31:26 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*create_redir(t_list **token)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	ft_memset(redir, 0, sizeof(t_redirect));
	redir->redir = ft_strdup(((t_token *)(*token)->content)->content);
	*token = (*token)->next;
	if (is_op(((t_token *)(*token)->content)->type))
		return (NULL);
	if (token && *token && (*token)->content)
	{
		redir->file = ft_strdup(((t_token *)(*token)->content)->content);
		*token = (*token)->next;
	}
	return (redir);
}

t_ast	*handle_redirect(t_ast *node, t_list **token, int is_first_call)
{
	t_ast	*redir_node;

	redir_node = malloc(sizeof(t_ast));
	if (!redir_node)
		return (NULL);
	ft_memset(redir_node, 0, sizeof(t_ast));
	redir_node->type = ((t_token *)(*token)->content)->type;
	redir_node->content = create_redir(token);
	if (is_first_call && node && node->type == CMD)
		redir_node->left = node;
	if (!redir_node->content)
	{
		free (redir_node);
		return (NULL);
	}
	if (*token && is_redirect(((t_token *)(*token)->content)->type))
		redir_node->right = handle_redirect(node, token, 0);
	return (redir_node);
}

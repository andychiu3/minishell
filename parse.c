/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:28:34 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/26 16:33:22 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(int type)
{
	return (type >= INPUT && type <= APPEND);
}

int	is_op(int type)
{
	return (type >= PIPE && type <= APPEND);
}

// too many lines
// t_ast	*add_redirect(t_list **token)
// {
// 	t_ast	*redir_node;

// 	redir_node = malloc(sizeof(t_ast));
// 	if (!redir_node)
// 		return (NULL);
// 	ft_memset(redir_node, 0, sizeof(t_ast));
// 	redir_node->type = ((t_token *)(*token)->content)->type;
// 	redir_node->content = malloc(sizeof(t_redirect));
// 	ft_memset(redir_node->content, 0, sizeof(t_redirect));
// 	if (!redir_node->content)
// 	{
// 		free (redir_node);
// 		return (NULL);
// 	}
// 	((t_redirect *)(redir_node->content))->redir
// 		= ((t_token *)(*token)->content)->content;
// 	*token = (*token)->next;
// 	if (token && *token && (*token)->content)
// 	{
// 		((t_redirect *)(redir_node->content))->file
// 			= ((t_token *)(*token)->content)->content;
// 		*token = (*token)->next;
// 	}
// 	if (*token && is_redirect(((t_token *)(*token)->content)->type))
// 		redir_node->right = add_redirect(token);
// 	return (redir_node);
// }

t_ast	*parser(t_list **tokens)
{
	t_ast	*node;

	node = NULL;
	while (tokens && *tokens)
	{
		if (((t_token *)((*tokens)->content))->type == CMD)
		{
			if (!node)
				node = create_cmd_node(tokens);
		}
		else if (is_redirect(((t_token *)((*tokens)->content))->type))
		{
			node = handle_redirect(node, tokens, 1);
			if (!node)
				return (NULL);
		}
		else if (((t_token *)((*tokens)->content))->type == PIPE)
		{
			node = handle_pipe(node, tokens);
			if (!node)
				return (NULL);
		}
		else
		{
			printf("minishell %s: command not found\n",
				(char *)((t_token *)((*tokens)->content))->content);
			return (NULL);
		}
	}
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:48:03 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/09 10:54:47 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_pipe_node(t_list **tokens)
{
	t_ast	*op_node;

	op_node = malloc(sizeof(t_ast));
	if (!op_node)
		return (NULL);
	op_node->type = ((t_token *)((*tokens)->content))->type;
	op_node->content = ft_strdup(((t_token *)((*tokens)->content))->content);
	op_node->left = NULL;
	op_node->right = NULL;
	(*tokens) = (*tokens)->next;
	return (op_node);
}

// idea of AST
// if op_node->right != CMD?
t_ast	*handle_pipe(t_ast *node, t_list **token)
{
	t_ast	*op_node;

	if (!node)
		return ((t_ast *)errormsg_exitcode("sytax", 258,
				(char *)((t_token *)((*token)->content))->content));
	op_node = create_pipe_node(token);
	op_node->left = node;
	if (token && *token && !is_redirect(((t_token *)((*token)->content))->type))
		op_node->right = parser(token);
	if (!op_node->right)
		return ((t_ast *)errormsg_exitcode("sytax", 258, "|"));
	printf("hi\n");
	return (op_node);
}

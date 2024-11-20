/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:48:03 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/11 10:07:14 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_pipe_node(t_list **tokens)
{
	t_ast	*op_node;

	op_node = malloc(sizeof(t_ast));
	if (!op_node)
		function_err_exit("malloc error");
	op_node->type = ((t_token *)((*tokens)->content))->type;
	op_node->content = ft_strdup(((t_token *)((*tokens)->content))->content);
	op_node->left = NULL;
	op_node->right = NULL;
	(*tokens) = (*tokens)->next;
	return (op_node);
}

// idea of AST
t_ast	*handle_pipe(t_ast *node, t_list **token, int *syntax_err, t_sh *sh)
{
	t_ast	*op_node;

	if (!node)
		return (syntax_error(syntax_err, 2));
	op_node = create_pipe_node(token);
	op_node->left = node;
	if (token && *token && ((t_token *)((*token)->content))->type != PIPE)
		op_node->right = parser(token, syntax_err, sh);
	if (!op_node->right)
	{
		free_ast(op_node);
		return (syntax_error(syntax_err, 2));
	}
	return (op_node);
}

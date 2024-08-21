/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:28:34 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/21 14:53:22 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_count(t_list *token)
{
	int	type;
	int	i;

	i = 0;
	while (token && (int)(*token)->type == ARG)
	{
		token = token->next;
		i++;
	}
	return (i);
}

t_ast	*create_cmd_node(t_list **tokens)
{
	t_ast	*cmd_node;
	int		i;

	cmd_node = malloc(sizeof(t_ast));
	if (!cmd_node)
		return (NULL);
	cmd_node->content = malloc(sizeof(t_cmd));
	if (!cmd_node->content)
	{
		free(cmd_node);
		return (NULL);
	}
	(t_cmd *)(cmd_node->content)->cmd = (t_token *)((*token)->content)->content;
	*token = (*token)->next;
	if (*token && (token *)((*token)->content)->type == ARG)
	{
		(t_cmd *)(cmd_node->content)->arg = malloc(arg_count(*token) + 1 * sizeof(char *));
		i = 0;
		while (*token && (t_token *)((*token)->content)->type == ARG)
		{
			(t_cmd *)(cmd_node->content)->arg[i++] = (**token)->content;
			*token = (*token)->next;
		}
		(t_cmd *)(cmd_node->content)->arg[i] = NULL;
	}
	return (cmd_node);
}

t_ast	*create_op_node(t_list **tokens)
{
	t_ast	*op_node;

	op_node = malloc(sizeof(t_ast));
	if (!op_node)
		return (NULL);
	op_node->content = ft_strdup((t_token *)((*token)->content)->content);
	op_node->left = NULL;
	op_node->right = NULL;
	(*token) = (*token)->next;
	return (op_node);
}

t_ast	parser(t_list **tokens)
{
	t_ast	*node;
	t_ast	*op_node;

	node = NULL;
	while (*tokens)
	{
		if (((t_token *)((*tokens)->content)->type == CMD)
		{
			if (!node)
				node = create_cmd_node(tokens);
		}
		else if (((t_token *)((*tokens)->content)->type >= PIPE
			&& ((t_token *)((*tokens)->content)->type <= APPEND)
		{
			op_node = create_op_node(tokens);
			op_node->left = node;
			node->right = parser(tokens);
			node = op_node;
		}
	}
	return (node);
}

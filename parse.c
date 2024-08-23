/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:28:34 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/23 16:25:45 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_count(t_list *token)
{
	int	i;

	i = 0;
	while (token && ((t_token *)((token)->content))->type == ARG)
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
		return ;
	i = 0;
	while (*token && ((t_token *)((*token)->content))->type == ARG)
	{
		cmd->arg[i++] = ft_strdup(((t_token *)((*token)->content))->content);
		*token = (*token)->next;
	}
	cmd->arg[i] = NULL;
}

int	is_redirect(int type)
{
	return (type >= INPUT && type <= APPEND);
}

t_ast	*create_cmd_node(t_list **tokens)
{
	t_ast	*cmd_node;

	cmd_node = malloc(sizeof(t_ast));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = ((t_token *)((*tokens)->content))->type;
	cmd_node->content = malloc(sizeof(t_cmd));
	if (!cmd_node->content)
	{
		free(cmd_node);
		return (NULL);
	}
	((t_cmd *)(cmd_node->content))->cmd
		= ((t_token *)((*tokens)->content))->content;
	((t_cmd *)(cmd_node->content))->arg = NULL;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	*tokens = (*tokens)->next;
	if (*tokens && ((t_token *)((*tokens)->content))->type == ARG)
		cmd_node_has_arg(cmd_node, tokens);
	// if (*tokens && is_redirect(((t_token *)((*tokens)->content))->type))
	// 	add_redirection(cmd_node, tokens);
	return (cmd_node);
}

// consider if ft_strdup fail?
t_ast	*create_op_node(t_list **tokens)
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
t_ast	*handle_op(t_ast *node, t_list **token)
{
	t_ast	*op_node;

	if (!node)
	{
		printf("minishell: syntax error near unexpected token '%s'\n",
			(char *)((t_token *)((*token)->content))->content);
		return (NULL);
	}
	op_node = create_op_node(token);
	op_node->left = node;
	if (token && *token && !is_redirect(((t_token *)((*token)->content))->type))
		op_node->right = create_cmd_node(token);
	if (!op_node->right)
	{
		printf("minishell: syntax error near unexpected token '%s'\n",
			(char *)((t_token *)((*token)->content))->content);
		return (NULL);
	}
	return (op_node);
}

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
		else if (((t_token *)((*tokens)->content))->type >= PIPE
			&& ((t_token *)((*tokens)->content))->type <= APPEND)
		{
			node = handle_op(node, tokens);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:28:34 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/15 09:44:54 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(int type)
{
	return (type >= INPUT && type <= HEREDOC);
}

int	is_op(int type)
{
	return (type >= PIPE && type <= HEREDOC);
}

t_ast	*parser(t_list **tokens)
{
	t_ast	*node;

	node = NULL;
	while (tokens && *tokens)
	{
		if (((t_token *)((*tokens)->content))->type == CMD)
			node = create_cmd_node(tokens);
		else if (is_redirect(((t_token *)((*tokens)->content))->type))
		{
			node = handle_redirect(node, tokens, 1, NULL);
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
			return ((t_ast *)errormsg_exitcode("nocmd",
					127, (char *)((t_token *)((*tokens)->content))->content));
	}
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:28:34 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 11:58:41 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_err_case(int syntax_err, t_list *token, t_sh *sh)
{
	if (syntax_err == 1)
		errormsg_exitcode("syntax", 2, NULL, sh);
	else if (syntax_err == 2)
		errormsg_exitcode("syntax", 2, "|", sh);
	else if (syntax_err == 3)
		errormsg_exitcode("syntax", 2,
			((t_token *)token->content)->content, sh);
}

// redir error: syntax_err = 1
// pipe error: syntax_err = 2
void	*syntax_error(int *syntax_err, int err_type)
{
	*syntax_err = err_type;
	return (NULL);
}

int	is_redirect(int type)
{
	return (type >= INPUT && type <= HEREDOC);
}

int	is_op(int type)
{
	return (type >= PIPE && type <= HEREDOC);
}

t_ast	*parser(t_list **tokens, int *syntax_err, t_sh *sh)
{
	t_ast	*node;

	node = NULL;
	while (tokens && *tokens && !sh->signaled && !*syntax_err)
	{
		if (!is_op(((t_token *)((*tokens)->content))->type))
			node = create_cmd_node(tokens);
		else if (is_redirect(((t_token *)((*tokens)->content))->type))
		{
			node = handle_init_redir(node, tokens, syntax_err, sh);
			if (!node)
				return (NULL);
		}
		else if (((t_token *)((*tokens)->content))->type == PIPE)
		{
			node = handle_pipe(node, tokens, syntax_err, sh);
			if (!node)
				return (NULL);
		}
	}
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_address.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:34:23 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/11 09:56:42 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->content);
	token->content = NULL;
	free(token);
	token = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->cmd)
		free(cmd->cmd);
	i = -1;
	if (cmd->arg)
	{
		while (cmd->arg[++i])
			free(cmd->arg[i]);
		free(cmd->arg);
	}
	free(cmd);
}

void	free_redir(t_redirect *redir)
{
	if (redir->redir)
		free(redir->redir);
	if (redir->file)
		free(redir->file);
	if (redir->heredoc_fd != -1)
	{
		close(redir->heredoc_fd);
		redir->heredoc_fd = -1;
	}
	free(redir);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == CMD)
		free_cmd((t_cmd *)(node->content));
	else if (node->type == PIPE)
		free(node->content);
	else if (is_redirect(node->type))
		free_redir((t_redirect *)(node->content));
	free(node);
}

void	ft_out(t_list *token, t_ast *node)
{
	if (token)
	{
		ft_lstclear(&token, free_token);
		token = NULL;
	}
	if (node)
	{
		free_ast(node);
		node = NULL;
	}
}

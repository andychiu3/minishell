/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:22:29 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/03 12:20:15 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prnt_strs(char **strs)
{
	if (!strs || !*strs)
		return ;
	while (*strs)
		printf("%s\n", *strs++);
}

void	prnt_token(t_list *token)
{
	t_token	*t;

	while (token)
	{
		t = (t_token *)token->content;
		printf("%s, type: %d\n", (char *)t->content, t->type);
		token = token->next;
	}
}

void	node_prnter(t_ast *node)
{
	t_cmd		*cmd;
	int			i;

	if (!node)
		return ;
	if (node->type == PIPE)
		err_printf("%s", (char *)node->content);
	else if (node->type == CMD)
	{
		cmd = node->content;
		err_printf("%s", cmd->cmd);
		i = -1;
		while (cmd->arg && cmd->arg[++i])
			err_printf(", %s", cmd->arg[i]);
	}
	else if (is_redirect(node->type))
	{
		err_printf("%s", ((t_redirect *)(node->content))->redir);
		if (((t_redirect *)(node->content))->file)
			err_printf(", %s", ((t_redirect *)(node->content))->file);
	}
	else
		err_printf("??%d\n", ((t_token *)(node->content))->type);
}

void	prnt_ast(t_ast *node, int level)
{
	int	i;

	if (!node)
		return ;
	i = -1;
	while (++i < level)
		err_printf("  ");
	node_prnter(node);
	printf("\n");
	prnt_ast(node->left, level + 1);
	prnt_ast(node->right, level + 1);
}

void	prnt_lst_node(t_list *lst_node)
{
	t_ast	*node;

	while (lst_node && lst_node->content)
	{
		node = (t_ast *)(lst_node->content);
		node_prnter(node);
		printf("\n");
		lst_node = lst_node->next;
	}
}

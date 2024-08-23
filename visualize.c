/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:22:29 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/23 11:08:32 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_cmd	*cmd;
	int		i;

	if (!node)
		return ;
	if (node->type >= PIPE && node->type <= APPEND)
	{
		ft_printf("%s", (char *)node->content);
	}
	else if (node->type == CMD)
	{
		cmd = node->content;
		ft_printf("%s", cmd->cmd);
		i = -1;
		while (cmd->arg && cmd->arg[++i])
			ft_printf(", %s", cmd->arg[i]);
	}
	else
		printf("what is this\n");
}

// right node with -> 
// left node with \n
// arg of cmd with ,
void	prnt_ast(t_ast *node)
{
	if (!node)
		return ;
	while (node)
	{
		node_prnter(node);
		if (node->right)
		{
			write(1, "      ->      ", 14);
			node_prnter(node->right);
		}
		node = node->left;
		printf("\n");
	}
}

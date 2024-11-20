/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:06:07 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/11 10:08:43 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_strncmp(str, "2>&1", sizeof(str)) == 0
// ft_strncmp(str, "1>&2", sizeof(str)) == 0
int	is_trunc(char *str)
{
	return (ft_strncmp(str, "2>", sizeof(str)) == 0
		|| ft_strncmp(str, ">", sizeof(str)) == 0);
}

// ft_strncmp(str, "2>>&1", sizeof(str)) == 0
// ft_strncmp(str, "1>>&2", sizeof(str)) == 0
int	is_append(char *str)
{
	return (ft_strncmp(str, "2>>", sizeof(str)) == 0
		|| ft_strncmp(str, ">>", sizeof(str)) == 0);
}

void	tokenize(char **array, t_list **token_list)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		function_err_exit("malloc error");
	if (ft_strncmp(*array, "|", sizeof(*array)) == 0)
		token->type = PIPE;
	else if (ft_strncmp("<", *array, sizeof(*array)) == 0)
		token->type = INPUT;
	else if (is_trunc(*array))
		token->type = TRUNC;
	else if (ft_strncmp("<<", *array, sizeof(*array)) == 0)
		token->type = HEREDOC;
	else if (is_append(*array))
		token->type = APPEND;
	else
		token->type = ARG;
	token->content = ft_strdup(*array);
	free(*array);
	*array = NULL;
	ft_lstadd_back(token_list, ft_lstnew((void *)token));
}

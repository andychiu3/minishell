/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:06:07 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/08 19:57:23 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd(char *str)
{
	return (ft_strncmp(str, "echo", sizeof(str)) == 0
		|| ft_strncmp(str, "cd", sizeof(str)) == 0
		|| ft_strncmp(str, "pwd", sizeof(str)) == 0
		|| ft_strncmp(str, "export", sizeof(str)) == 0
		|| ft_strncmp(str, "unset", sizeof(str)) == 0
		|| ft_strncmp(str, "env", sizeof(str)) == 0
		|| ft_strncmp(str, "exit", sizeof(str)) == 0);
}

t_token	*tokenize(char *array)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (is_cmd(array))
		token->type = CMD;
	else if (ft_strncmp(array, "|", sizeof(array)) == 0)
		token->type = PIPE;
	else if (ft_strncmp("$", array, 1) == 0)
		token->type = VAR;
	else if (ft_strncmp("<", array, sizeof(array)) == 0)
		token->type = INPUT;
	else if (ft_strncmp(">", array, sizeof(array)) == 0)
		token->type = TRUNC;
	else if (ft_strncmp(">>", array, sizeof(array)) == 0)
		token->type = HEREDOC;
	else if (ft_strncmp("<<", array, sizeof(array)) == 0)
		token->type = APPEND;
	else
		token->type = ARG;
	token->content = array;
	return (token);
}

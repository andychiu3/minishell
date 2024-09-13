/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:06:07 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/13 14:15:42 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd(char **str, t_sh *sh)
{
	char	*path;

	if (ft_strcmp(*str, "..") == 0 || ft_strcmp(*str, ".") == 0)
		return (0);
	if (ft_strcmp(*str, "export") == 0
		|| ft_strcmp(*str, "unset") == 0
		|| ft_strcmp(*str, "exit") == 0)
		return (1);
	path = is_executable(*str, sh);
	if (path)
		return (1);
	else
		return (0);
}

int	is_trunc(char *str)
{
	return (ft_strncmp(str, "2>", sizeof(str)) == 0
		|| ft_strncmp(str, ">", sizeof(str)) == 0
		|| ft_strncmp(str, "2>&1", sizeof(str)) == 0
		|| ft_strncmp(str, "1>&2", sizeof(str)) == 0);
}

int	is_append(char *str)
{
	return (ft_strncmp(str, "2>>", sizeof(str)) == 0
		|| ft_strncmp(str, ">>", sizeof(str)) == 0
		|| ft_strncmp(str, "2>>&1", sizeof(str)) == 0
		|| ft_strncmp(str, "1>>&2", sizeof(str)) == 0);
}

void	tokenize(char *array, t_list **token_list, t_sh *sh)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	if (is_cmd(&array, sh))
		token->type = CMD;
	else if (ft_strncmp(array, "|", sizeof(array)) == 0)
		token->type = PIPE;
	else if (ft_strncmp("$", array, 1) == 0)
		token->type = VAR;
	else if (ft_strncmp("<", array, sizeof(array)) == 0)
		token->type = INPUT;
	else if (is_trunc(array))
		token->type = TRUNC;
	else if (ft_strncmp("<<", array, sizeof(array)) == 0)
		token->type = HEREDOC;
	else if (is_append(array))
		token->type = APPEND;
	else
		token->type = ARG;
	token->content = array;
	ft_lstadd_back(token_list, ft_lstnew((void *)token));
}

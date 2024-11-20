/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <achiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:34:45 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/14 16:13:27 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract(char *str, int *i, int *quote)
{
	char	*new;
	int		start;

	new = NULL;
	start = *i;
	while (*i < (int)ft_strlen(str))
	{
		if (*quote == NONE
			&& (ft_strchr("|<>", str[*i]) || space_or_tab(str[*i])))
			break ;
		(*i)++;
		*quote = if_quote(str[*i], *quote);
	}
	new = ft_substr(str, start, *i - start);
	return (new);
}

char	*extract_op(char *str, int *start, int *i)
{
	char	*new;

	new = NULL;
	(*i)++;
	if (str[*start] == '>' || str[*start] == '<')
		if (str[*start] == str[*start + 1])
			(*i)++;
	new = ft_substr(str, *start, (*i) - *start);
	return (new);
}

void	lexer(char *line, t_list **token_list)
{
	int		quote;
	int		i;
	int		start;
	char	*array;

	quote = NONE;
	i = 0;
	while (line[i])
	{
		start = i;
		quote = if_quote(line[i], quote);
		if (quote == NONE && space_or_tab(line[i]))
		{
			while (quote == NONE && space_or_tab(line[i]))
				i++;
			continue ;
		}
		else if (quote == NONE && ft_strchr("|<>", line[i]))
			array = extract_op(line, &start, &i);
		else
			array = extract(line, &i, &quote);
		if (array)
			tokenize(&array, token_list);
	}
}

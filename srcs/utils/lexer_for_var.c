/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_for_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:32:37 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/11 10:56:39 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_in_var(char *str, int *i, int *quote)
{
	char	*new;
	int		start;

	new = NULL;
	start = *i;
	while (*i < (int)ft_strlen(str))
	{
		if (*quote == NONE && str[*i] == ' ')
			break ;
		(*i)++;
		*quote = if_quote(str[*i], *quote);
	}
	new = ft_substr(str, start, *i - start);
	return (new);
}

char	**lexer_for_var(char *line)
{
	int		quote;
	int		i;
	char	*array;
	char	**strs;

	strs = NULL;
	quote = NONE;
	i = 0;
	while (i < (int)ft_strlen(line))
	{
		quote = if_quote(line[i], quote);
		while (quote == NONE && line[i] == ' ')
			i++;
		array = extract_in_var(line, &i, &quote);
		if (array)
		{
			add_str_to_strs(&strs, array);
			free(array);
			array = NULL;
		}
	}
	return (strs);
}

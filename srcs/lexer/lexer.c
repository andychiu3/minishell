/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:34:45 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/14 08:58:57 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract(char *str, int *i, t_sh *sh, int *quote)
{
	char	*new;
	char	*tmp;
	int		start;

	new = NULL;
	start = *i;
	while (*i < (int)ft_strlen(str))
	{
		if (*quote == NONE && (ft_strchr("|<>", str[*i]) || str[*i] == ' '))
			break ;
		(*i)++;
		*quote = if_quote(str[*i], *quote);
	}
	new = ft_substr(str, start, *i - start);
	tmp = var_situation(new, sh);
	free(new);
	if (tmp)
	{
		new = remove_quote(tmp);
		free(tmp);
	}
	else
		new = NULL;
	return (new);
}

char	*extract_op(char *str, int *start, int *i)
{
	char	*new;

	new = NULL;
	// printf("before i: %d, s: %d\n", *i, *start);
	(*i)++;
	if (str[*start] == '>' || str[*start] == '<')
		if (str[*start] == str[*start + 1])
			(*i)++;
	new = ft_substr(str, *start, (*i) - *start);
	// printf("after i: %d, s: %d\n", *i, *start);
	return (new);
}

void	lexer(char *line, t_list **token_list, t_sh *sh)
{
	int		quote;
	int		i;
	int		start;
	char	*array;

	quote = NONE;
	i = 0;
	while (i < (int)ft_strlen(line))
	{
		start = i;
		quote = if_quote(line[i], quote);
		if (quote == NONE && line[i] == ' ')
		{
			while (quote == NONE && line[i] == ' ')
				i++;
			continue ;
		}
		else if (quote == NONE && ft_strchr("|<>", line[i]))
			array = extract_op(line, &start, &i);
		else
			array = extract(line, &i, sh, &quote);
		if (array)
			tokenize(array, token_list, sh);
	}
}

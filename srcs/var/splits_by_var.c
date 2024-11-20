/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_by_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:11:28 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/11 11:25:26 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if start as a VAR
int	var_(char *str, int quote, int i)
{
	return (str[i] == '$' && str[i + 1] != '$'
		&& quote != SINGLE && str[i + 1]);
}

void	normal_word_ends(char *str, int *quote, int *i, int *count)
{
	while (str[*i] && !var_(str, *quote, *i))
	{
		(*i)++;
		*quote = if_quote(str[*i], *quote);
	}
	if (count != NULL)
		(*count)++;
}

void	var_ends(char *str, int *i, int *count)
{
	(*i)++;
	if (str[*i] == '?')
		(*i)++;
	else
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
	if (count != NULL)
		(*count)++;
}

int	split_count(char *str)
{
	int	i;
	int	quote;
	int	count;

	count = 0;
	i = 0;
	quote = NONE;
	while (str[i])
	{
		quote = if_quote(str[i], quote);
		if (var_(str, quote, i))
			var_ends(str, &i, &count);
		else
			normal_word_ends(str, &quote, &i, &count);
	}
	return (count);
}

// can only be used when if (str) cuz too many lines
char	**split_by_var(char *str)
{
	int		i;
	int		quote;
	char	**splits;
	int		start;
	int		y;

	splits = malloc((split_count(str) + 1) * sizeof(char *));
	if (!splits)
		return (NULL);
	i = 0;
	quote = NONE;
	y = 0;
	while (str[i])
	{
		start = i;
		quote = if_quote(str[i], quote);
		if (var_(str, quote, i))
			var_ends(str, &i, NULL);
		else
			normal_word_ends(str, &quote, &i, NULL);
		splits[y++] = ft_substr(str, start, i - start);
	}
	splits[y] = NULL;
	return (splits);
}

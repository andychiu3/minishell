/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:39:11 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/19 11:56:04 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_valid(char *line, t_sh *sh)
{
	if (quote_case(line) == SINGLE)
	{
		errormsg_exitcode("EOF", 1, "'", sh);
		return (0);
	}
	else if (quote_case(line) == DOUBLE)
	{
		errormsg_exitcode("EOF", 1, "\"", sh);
		return (0);
	}
	return (1);
}

// is quote closed
int	quote_case(char *line)
{
	int	i;
	int	quote;

	i = -1;
	quote = NONE;
	while (++i < (int)ft_strlen(line))
	{
		if (line[i] == '\'' && quote == NONE)
			quote = SINGLE;
		else if (line[i] == '\'' && quote == SINGLE)
			quote = NONE;
		else if (line[i] == '\"' && quote == NONE)
			quote = DOUBLE;
		else if (line[i] == '\"' && quote == DOUBLE)
			quote = NONE;
	}
	return (quote);
}

// update char c quote situation
int	if_quote(char c, int quote)
{
	if (c == '\'' && quote == NONE)
		quote = SINGLE;
	else if (c == '\'' && quote == SINGLE)
		quote = NONE;
	else if (c == '\"' && quote == NONE)
		quote = DOUBLE;
	else if (c == '\"' && quote == DOUBLE)
		quote = NONE;
	return (quote);
}

// remove the quote after substr
char	*remove_quote(char *str)
{
	char	*new;
	int		i;
	int		quote;

	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	quote = NONE;
	while (*str)
	{
		quote = if_quote(*str, quote);
		if (*str != '\'' && *str != '\"')
			new[i++] = *str;
		else if ((*str == '\'' && quote == DOUBLE)
			|| (*str == '\"' && quote == SINGLE))
			new[i++] = *str;
		str++;
	}
	new[i] = '\0';
	return (new);
}

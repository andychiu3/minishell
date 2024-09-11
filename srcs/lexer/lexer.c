/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:34:45 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/11 13:39:30 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // if quote valid
// // CONSIDER IF WE KEEP IT AFTER AST
// int	quote_case(char *line)
// {
// 	int	i;
// 	int	quote;

// 	i = -1;
// 	quote = NONE;
// 	while (++i < (int)ft_strlen(line))
// 	{
// 		if (line[i] == '\'' && quote == NONE)
// 			quote = SINGLE;
// 		else if (line[i] == '\'' && quote == SINGLE)
// 			quote = NONE;
// 		else if (line[i] == '\"' && quote == NONE)
// 			quote = DOUBLE;
// 		else if (line[i] == '\"' && quote == DOUBLE)
// 			quote = NONE;
// 	}
// 	return (quote == NONE);
// }

// // update char c quote situation
// int	if_quote(char c, int quote)
// {
// 	if (c == '\'' && quote == NONE)
// 		quote = SINGLE;
// 	else if (c == '\'' && quote == SINGLE)
// 		quote = NONE;
// 	else if (c == '\"' && quote == NONE)
// 		quote = DOUBLE;
// 	else if (c == '\"' && quote == DOUBLE)
// 		quote = NONE;
// 	return (quote);
// }

// // remove the quote after substr
// char	*remove_quote(char *str)
// {
// 	char	*new;
// 	int		i;
// 	int		quote;

// 	if (!str)
// 		return (NULL);
// 	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
// 	if (!new)
// 		return (NULL);
// 	i = 0;
// 	quote = NONE;
// 	while (*str)
// 	{
// 		quote = if_quote(*str, quote);
// 		if (*str != '\'' && *str != '\"')
// 			new[i++] = *str;
// 		else if ((*str == '\'' && quote == DOUBLE)
// 			|| (*str == '\"' && quote == SINGLE))
// 			new[i++] = *str;
// 		str++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

// ignoring ' ' when no quote -> update START
// no need to update the int *i tho
// get the token->content if valid
// char	*extract(char *str, int *start, int *i, t_sh *sh)
// {
// 	char	*new;
// 	char	*tmp;

// 	new = NULL;
// 	if (*i == 0 || str[*i - 1] == ' ')
// 		(*start) = *i + 1;
// 	else
// 	{
// 		new = ft_substr(str, *start, *i - *start);
// 		tmp = var_situation(new, sh);
// 		free(new);
// 		if (tmp)
// 		{
// 			new = remove_quote(tmp);
// 			free(tmp);
// 		}
// 		else
// 			new = NULL;
// 		*start = *i + 1;
// 	}
// 	return (new);
// }

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
		// printf("char c: %c\n", line[i]);
		quote = if_quote(line[i], quote);
		if (quote == NONE && line[i] == ' ')
		{
			while (quote == NONE && line[i] == ' ')
			{
				// printf("skip space and i: %d\n", i);
				i++;
			}
			continue ;
		}
		else if (quote == NONE && ft_strchr("|<>", line[i]))
		{
			// printf("op and i: %d\n", i);
			array = extract_op(line, &start, &i);
		}
		else
		{
			// printf("words and i: %d\n", i);
			array = extract(line, &i, sh, &quote);
		}
		if (array)
		{
			tokenize(array, token_list, sh);
			// free(array);
		}
		// printf("\n");
	}
}

// check the READLINE including last \0 so (int)ft_strlen(line) + 1
// void	lexer(char *line, t_list **token_list, t_sh *sh)
// {
// 	int		quote;
// 	int		i;
// 	int		start;
// 	char	*array;

// 	start = 0;
// 	quote = NONE;
// 	i = -1;
// 	while (++i < (int)ft_strlen(line) + 1)
// 	{
// 		quote = if_quote(line[i], quote);
// 		if (quote == NONE
// 			&& (line[i] == ' ' || line[i] == '\0' ))
// 		{
// 			array = extract(line, &start, &i, sh);
// 			if (array)
// 				tokenize(array, token_list, sh);
// 		}
// 	}
// }
//  || ft_strchr("|<>", line[i])

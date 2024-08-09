/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:34:45 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/08 21:45:33 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if quote valid
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
	return (quote == NONE);
}

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

char	*remove_quote(char *str)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str != '\'' && *str != '\"')
			new[i++] = *str;
		str++;
	}
	new[i] = '\0';
	return (new);
}

char	*extract(char *str, int *start, int *i)
{
	char	*new;

	new = NULL;
	if (*i == 0 || str[*i - 1] == ' ')
		(*start) = *i + 1;
	else
	{
		new = ft_substr(str, *start, *i - *start);
		new = remove_quote(new);
		*start = *i + 1;
	}
	return (new);
}

void	lexer_(char *line)
{
	t_list	*token;
	int		quote;
	int		i;
	int		start;
	char	*array;

	if (!line)
		return ;
	i = -1;
	start = 0;
	token = NULL;
	quote = NONE;
	while (++i < (int)ft_strlen(line) + 1)
	{
		quote = if_quote(line[i], quote);
		if (quote == NONE && (line[i] == ' ' || line[i] == '\0'))
		{
			array = extract(line, &start, &i);
			if (array)
				ft_lstadd_back(&token, ft_lstnew((void *)array));
		}
	}
	while (token)
	{
		printf("%s\n", (char *)token->content);
		token = token->next;
	}
	if (quote != NONE)
		perror("unclosed quote");
}

void	lexer(char *line, t_list **token_list)
{
	int		quote;
	int		i;
	int		start;
	char	*array;
	t_token	*token;

	start = 0;
	quote = NONE;
	i = -1;
	while (++i < (int)ft_strlen(line) + 1)
	{
		quote = if_quote(line[i], quote);
		if (quote == NONE && (line[i] == ' ' || line[i] == '\0'))
		{
			array = extract(line, &start, &i);
			if (array)
			{
				token = tokenize(array);
				ft_lstadd_back(token_list, ft_lstnew((void *)token));
			}
		}
	}
}

void	scanning(char *line)
{
	t_list	*token;

	if (!line)
		return ;
	if (!quote_case(line))
	{
		printf("unclosed quotes\n");
		return ;
	}
	token = NULL;
	lexer(line, &token);
	while (token)
	{
		t_token *t = (t_token *)token->content;
		printf("%s, type: %d\n", (char *)t->content, t->type);
		token = token->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:43:28 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/08 19:03:55 by fiftyblue        ###   ########.fr       */
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

// extract the quote and renew the ptr
char	*extract_quote(char **line, char c)
{
	int		len;
	char	*next;
	char	*origin;

	if (**line == c)
		(*line)++;
	origin = *line;
	next = ft_strchr(*line, c);
	if (!next)
		return (NULL);
	if (*(next + 1) != ' ' && *(next + 1) != '\0')
		return (extract_(line, ' '));
	len = next - *line;
	*line = next + 1;
	return (ft_substr(origin, 0, len));
}

// quotes in normal words. ex: e"c"'h'o
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

// extract non-quote words which may have quotes in it and renew ptr
// if there is a before space
char	*extract_(char **line, char c)
{
	int		len;
	char	*next;
	char	*origin;
	char	*tmp;

	origin = *line;
	next = ft_strchr(*line, c);
	tmp = ft_strchr(*line, '\'');
	if (tmp)
		if (next - tmp > 0)
			tmp = ft_strchr(tmp, '\'');
	
	if (!next)
		len = ft_strlen(*line);
	else
		len = ft_strchr(*line, c) - *line;
	if (next)
		*line = next + 1;
	else
		*line = NULL;
	tmp = ft_substr(origin, 0, len);
	tmp = remove_quote(tmp);
	return (tmp);
}

char	*if_word(char *line, char c)
{
	int	quote;
	int	i;
	int	start;
	int	end;

	i = -1;
	quote = NONE;
	start = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && quote == NONE)
		{
			quote = SINGLE;
		}
		else if (line[i] == '\"' && quote == NONE)
		{
			quote = DOUBLE;
		}
		else if (line[i] == '\'' && quote == SINGLE)
		{
			quote = NONE;
		}
		else if (line[i] == '\'' && quote == SINGLE)
		{
			quote = NONE;
		}
		else if ((line[i] == ' ' || line[i] == '\0') && quote == NONE)
			end = i - 1;
	}
}

void	tokenize(char *line, t_list **token)
{
	char	*array;

	while (line && *line)
	{
		if (ft_isspace(*line))
			line++;
		else if (*line == '\'')
			array = extract_quote(&line, '\'');
		else if (*line == '\"')
			array = extract_quote(&line, '\"');
		else
			array = extract_(&line, ' ');
		if (array)
		{
			ft_lstadd_back(token, ft_lstnew((void *)array));
		}
	}
}

// tokenize -> 
void	lexical(char *line)
{
	t_list	*token;

	if (!line)
		return ;
	if (!quote_case(line))
	{
		perror("unclosed quotes");
		return ;
	}
	token = NULL;
	tokenize(line, &token);
	while (token)
	{
		printf("%s\n", (char *)token->content);
		token = token->next;
	}
}

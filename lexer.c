/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:34:45 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/08/27 09:08:03 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if quote valid
// CONSIDER IF WE KEEP IT AFTER AST
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

// ignoring ' ' when no quote -> update START
// no need to update the int *i tho
// get the token->content if valid
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

// check the READLINE including last \0 so (int)ft_strlen(line) + 1
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

// void	scanning(char *line)
// {
// 	t_list	*token;
// 	t_ast	*root;

// 	if (!line)
// 		return ;
// 	if (!quote_case(line))
// 	{
// 		printf("unclosed quotes\n");
// 		return ;
// 	}
// 	token = NULL;
// 	lexer(line, &token);
// 	// prnt_token(token);
// 	root = NULL;
// 	root = parser(&token);
// 	// prnt_ast(root, 0);
// 	ft_out(token, root);
// }

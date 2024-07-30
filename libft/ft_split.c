/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <achiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:11:29 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/03/18 13:32:27 by achiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counts(char const *s, char c)
{
	int	trigger;
	int	i;

	trigger = 0;
	i = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			i++;
			trigger = 1;
		}
		if (*s == c)
			trigger = 0;
		s++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word || !str)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	free_array(size_t i, char **array)
{
	while (i--)
		free(array[i]);
	free (array);
}

static char	**get_wrd(char const *s, char c, char **dest)
{
	size_t	i;
	size_t	j;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			dest[j++] = word_dup(s, index, i);
			if (!dest[j - 1])
			{
				free_array(j, dest);
				return (0);
			}
			index = -1;
		}
		i++;
	}
	dest[j] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	split = malloc((word_counts(s, c) + 1) * sizeof(char *));
	if (!split || !s)
		return (0);
	split = get_wrd(s, c, split);
	if (!split)
		return (0);
	return (split);
}

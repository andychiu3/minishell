#include "libft.h"

int	ft_isnbr(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '+' || str[i] == '-')
			i++;
		if (str[i] == '\0')
			return (0);
		while (str[i] && str[i] != ' ')
			if (!ft_isdigit(str[i++]))
				return (0);
		while (str[i] == ' ')
			i++;
		return ((size_t)i == ft_strlen(str));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:57:48 by achiu             #+#    #+#             */
/*   Updated: 2024/03/17 07:48:41 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		count;

	count = ft_count(n);
	dest = ft_calloc(count + 1, 1);
	if (!dest)
		return (0);
	if (n == -2147483648)
		return (ft_memcpy(dest, "-2147483648", 12));
	if (n == 0)
		dest[0] = '0';
	if (n < 0)
	{
		dest[0] = '-';
		n = -n;
	}
	dest[count] = 0;
	while (n)
	{
		dest[--count] = n % 10 + '0';
		n /= 10;
	}
	return (dest);
}

/*
1. min value
2. intput 0
3. didn't use the malloc space for above cases
4. too many lines in a function

int	main(void)
{
	printf("%s", ft_itoa(123456789));
	return (0);
}
*/

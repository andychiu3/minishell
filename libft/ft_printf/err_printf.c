/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:59:07 by achiu             #+#    #+#             */
/*   Updated: 2024/09/16 08:21:49 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	err_printf(const char *str, ...)
{
	va_list		args;
	int			len;
	int			i;

	va_start(args, str);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[++i])
			ft_conversion(&args, str[i], &len);
		else
			ft_print_count(str[i], &len);
		i++;
	}
	va_end(args);
	return (len);
}

void	ft_conversion(va_list *args, char c, int *len)
{
	if (c == 'c')
		ap_putchar(args, len);
	else if (c == 's')
		ap_putstr(va_arg(*args, char *), len);
	else if (c == 'p')
		ap_puthex_adr(va_arg(*args, void *), len, c);
	else if (c == 'd' || c == 'i')
		ap_nbr(args, len);
	else if (c == 'u')
		ap_unbr(args, len);
	else if (c == 'x' || c == 'X')
		ap_puthex(va_arg(*args, unsigned int), len, c);
	else if (c == '%')
		ft_print_count('%', len);
}

void	ft_print_count(char c, int *len)
{
	if (*len == -1)
		return ;
	if (write(STDERR_FILENO, &c, 1) == -1)
	{
		*len = -1;
		return ;
	}
	*len += 1;
}

// int	main(void)
// {
// 	int len;
// 	len = ft_printf("%u\n", -10);
// 	printf("my len: %d\n", len);
// 	len = printf("%u\n", -10);
// 	printf("real len: %d\n", len);
// 	return 0;
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:29:48 by achiu             #+#    #+#             */
/*   Updated: 2024/06/17 14:39:59 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ap_nbr(va_list *args, int *len)
{
	int	nbr;

	nbr = va_arg(*args, int);
	if (nbr == -2147483648)
	{
		ap_putstr("-2", len);
		nbr = 147483648;
	}
	if (nbr < 0)
	{
		ft_print_count('-', len);
		nbr = -nbr;
	}
	ap_putnbr(nbr, len);
}

void	ap_unbr(va_list *args, int *len)
{
	unsigned int	nbr;

	nbr = va_arg(*args, unsigned int);
	ap_putnbr(nbr, len);
}

void	ap_putnbr(unsigned int nbr, int *len)
{
	while (nbr >= 10)
	{
		ap_putnbr(nbr / 10, len);
		nbr = (nbr % 10);
	}
	ft_print_count(nbr + '0', len);
}

// void	ap_putunbr(va_list args, int len)
// {
// 	int	nbr;

// 	nbr = va_arg(args, unsigned int);
// 	while (nbr >= 10)
// 	{
// 		ft_putnbr(nbr / 10, len);
// 		nbr = (nbr % 10);
// 	}
// 	ft_print_count(nbr + '0', len);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:29:03 by achiu             #+#    #+#             */
/*   Updated: 2024/06/17 14:40:12 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ap_puthex(unsigned long hex, int *len, char c)
{
	while (hex >= 16)
	{
		ap_puthex(hex / 16, len, c);
		hex = hex % 16;
	}
	if (hex <= 9)
		hex = hex + '0';
	else
	{
		if (c == 'x' || c == 'p')
			hex = hex - 10 + 'a';
		if (c == 'X')
			hex = hex - 10 + 'A';
	}
	ft_print_count(hex, len);
}

void	ap_puthex_adr(void *ptr, int *len, char c)
{
	ap_putstr("0x", len);
	ap_puthex((unsigned long)ptr, len, c);
}

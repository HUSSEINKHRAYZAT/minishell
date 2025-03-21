/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:29:07 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/08/08 17:29:08 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hexa_helperp(unsigned long long p)
{
	const char	*s;
	int			c;

	s = "0123456789abcdef";
	if (p == 0)
		return ;
	else
	{
		c = p % 16;
		print_hexa_helperp(p / 16);
		write(1, &s[c], 1);
	}
}

int	count_hexap(unsigned long long p)
{
	if (p == 0)
		return (0);
	else
		return (1 + count_hexap(p / 16));
}

int	print_hexap(unsigned long long p)
{
	if (p == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	print_hexa_helperp(p);
	return (2 + count_hexap(p));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:29:30 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/08/08 17:29:31 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	size_of_int(int n)
{
	if (n / 10 == 0)
		return (1);
	else
		return (1 + size_of_int(n / 10));
}

void	ft_putnbr_int(int n)
{
	char	c;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		ft_putnbr_int(n);
	}
	else
	{
		if (n / 10 == 0)
		{
			c = n + '0';
			write(1, &c, 1);
		}
		else
		{
			c = n % 10 + '0';
			ft_putnbr_int(n / 10);
			write(1, &c, 1);
		}
	}
}

int	print_int(int n)
{
	ft_putnbr_int(n);
	if (n >= 0)
		return (size_of_int(n));
	else
		return (size_of_int(n) + 1);
}

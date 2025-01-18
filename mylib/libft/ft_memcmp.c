/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:49:17 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/07/14 14:49:21 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str_s1;
	unsigned char	*str_s2;

	i = 0;
	str_s1 = (unsigned char *)s1;
	str_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str_s1[i] == str_s2[i] && i < n - 1)
	{
		i++;
	}
	return (str_s1[i] - str_s2[i]);
}

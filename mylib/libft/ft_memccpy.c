/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:46:44 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/07/14 14:46:47 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*str_dest;
	unsigned char	*str_src;

	str_dest = (unsigned char *)dest;
	str_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		str_dest[i] = str_src[i];
		if (str_dest[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}

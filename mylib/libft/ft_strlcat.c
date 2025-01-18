/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:50:41 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/07/14 14:50:44 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	m;
	size_t	p;

	m = 0;
	n = ft_strlen(dst);
	p = ft_strlen(src);
	if (size == 0)
		return (p);
	while ((src[m] != '\0') && ((n + m) < (size - 1)))
	{
		dst[n + m] = src[m];
		m++;
	}
	dst[n + m] = '\0';
	if (size > n)
		return (n + p);
	return (size + p);
}

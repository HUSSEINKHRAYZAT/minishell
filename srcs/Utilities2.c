/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:56:18 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/15 17:54:12 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	result = (char *)malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	ft_strcat(result, s3);
	return (result);
}

// Use the syscall for getpid

pid_t	ft_getpid(void)
{
	return (syscall(SYS_getpid));
}

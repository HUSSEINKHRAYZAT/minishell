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
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;
	int		i;
	pid_t	pid;

	i = 0;
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read <= 0)
		return (-1);
	buffer[bytes_read] = '\0';
	while (buffer[i] >= '0' && buffer[i] <= '9')
		i++;
	buffer[i] = '\0';
	pid = (pid_t)ft_atoi(buffer);
	return (pid);
}

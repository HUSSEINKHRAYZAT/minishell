/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:37:15 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/06/21 12:53:11 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stddef.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);
char	*ft_strdup(char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);

#endif

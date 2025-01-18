/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:28:50 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/08/08 17:30:00 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_strlenn(const char *str);
int		ft_putstr(char *s);
int		print_int(int n);
int		print_unsigned_long_long(unsigned long long n);
int		print_ul(unsigned long n);
int		print_hexab(unsigned int n);
int		print_hexas(unsigned int n);
int		print_hexap(unsigned long long p);
int		print_ui(unsigned int n);

#endif
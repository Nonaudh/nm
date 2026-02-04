/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:45:21 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/09 16:06:43 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H
# include <unistd.h>
# include <stdarg.h>

int	ft_dprintf(int fd, const char *str, ...);
int	ft_ddecimal_lenght(long n);
int	ft_dhexadecimal_lenght(unsigned long n);
int	ft_dprint_character(int fd, int c);
int	ft_dprint_string(int fd, char *str);
int	ft_dprint_pointer_hexadecimal(int fd, unsigned long n);
int	ft_dprint_pointer(int fd, unsigned long n);
int	ft_dprint_integer(int fd, long n);
int	ft_dprint_unsigned_decimal(int fd, unsigned int n);
int	ft_dprint_hexadecimal(int fd, unsigned int n, char format);
int	set_dformat(int fd, va_list args, char c);

#endif

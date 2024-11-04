/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:22:17 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/07 12:54:43 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// # include <ctype.h>
# include <stdarg.h>
// # include <stddef.h>
// # include <stdint.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
int		ft_put_unsigned_decimal(unsigned int i);
int		ft_putchar(int c);
int		ft_puthexa(unsigned int i, char c);
int		ft_putnumber(int i);
int		ft_putptr(void *ptr);
int		ft_putstr(char *str);
char	*ft_strcpy(char *dest, char *src);

#endif

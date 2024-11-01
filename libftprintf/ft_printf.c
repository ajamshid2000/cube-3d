/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:27:16 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/21 08:45:37 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ss;
	unsigned char	cc;

	ss = (unsigned char *)s;
	cc = (unsigned char)c;
	while (*ss != '\0')
	{
		if (*ss == cc)
			return ((char *)ss);
		ss++;
	}
	if (c == 0)
		return ((char *)ss);
	return (0);
}

int	ft_write(va_list args, char *str)
{
	if (*str == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (*str == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (*str == 'p')
		return (ft_putptr(va_arg(args, void *)));
	if (*str == 'd' || *str == 'i')
		return (ft_putnumber(va_arg(args, int)));
	if (*str == 'u')
		return (ft_put_unsigned_decimal(va_arg(args, unsigned int)));
	if (*str == 'x' || *str == 'X')
		return (ft_puthexa(va_arg(args, int), *str));
	if (*str == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		counter;
	va_list	args;
	int		i;

	if (!str)
		return (-1);
	va_start(args, str);
	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && ft_strchr("cspdiuxX%", str[i + 1]))
		{
			counter += ft_write(args, (char *)&str[++i]);
		}
		else
			counter += ft_putchar(str[i]);
		i++;
	}
	return (counter);
}

// #include <stdio.h>
// int main()
// {
// 	printf("Width: %02d, Precision: %.2f\n", 1, 3.14159);
// 	ft_printf("Width: %02d, Precision: %.2f\n", 123, 3.14159);

// }
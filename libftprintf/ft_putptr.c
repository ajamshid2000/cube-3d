/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:08:04 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/28 23:07:01 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printptr(unsigned long i)
{
	char	hexa[17];
	int		counter;

	counter = 0;
	ft_strcpy(hexa, "0123456789abcdef");
	if (i > 15)
		counter += ft_printptr((i / 16));
	counter += ft_putchar(hexa[i % 16]);
	return (counter);
}

int	ft_putptr(void *ptr)
{
	int				counter;
	unsigned long	i;

	counter = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	i = (unsigned long)ptr;
	counter += ft_putstr("0x");
	return (counter += ft_printptr(i));
}

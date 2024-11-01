/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:28:42 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/30 01:16:15 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa(unsigned int i, char c)
{
	size_t	j;
	char	hexa[17];
	int		counter;

	counter = 0;
	j = 9;
	ft_strcpy(hexa, "0123456789abcdef");
	if (c == 'X')
		while (j++ < 16)
			hexa[j] = hexa[j] - 32;
	if (i > 15)
		counter += ft_puthexa((i / 16), c);
	counter += ft_putchar(hexa[i % 16]);
	return (counter);
}

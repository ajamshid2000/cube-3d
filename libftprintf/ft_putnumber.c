/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:15:23 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/05 16:06:56 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnumber(int i)
{
	int	counter;

	counter = 1;
	if (i == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (i < 0)
	{
		ft_putchar('-');
		i = -i;
		counter++;
	}
	if (i > 9)
		counter += ft_putnumber(i / 10);
	ft_putchar(i % 10 + '0');
	return (counter);
}

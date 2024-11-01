/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_decimal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:15:23 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/05 16:08:44 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_unsigned_decimal(unsigned int i)
{
	int	counter;

	counter = 1;
	if (i > 9)
		counter += ft_put_unsigned_decimal(i / 10);
	ft_putchar(i % 10 + '0');
	return (counter);
}

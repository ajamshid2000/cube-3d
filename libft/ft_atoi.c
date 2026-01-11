/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yand <mel-yand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:39:59 by ajamshid          #+#    #+#             */
/*   Updated: 2024/12/02 16:36:06 by mel-yand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  #include <stdio.h>
#include "libft.h"

int ft_atoi(const char *nptr)
{
	int res;
	int i;
	int sign;

	res = 0;
	i = 0;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	if (!(nptr[i] <= '9' && nptr[i] >= '0'))
		return (-1);
	while (nptr[i] <= '9' && nptr[i] >= '0' && i < 10)
		res = res * 10 + nptr[i++] - '0';
	if (!(nptr[i] <= '9' && nptr[i] >= '0') && nptr[i] != '\0')
		return (-1);
	return (res * sign);
}

// int	main(void)
// {
// 	char numbers[] = "\t   ---++--2147483648";
// 	printf("%d", ft_atoi(numbers));

// }

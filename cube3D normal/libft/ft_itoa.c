/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:30:13 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/07 10:31:29 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

size_t	counter(int n)
{
	int	i;

	i = 1;
	n /= 10;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	num;
	size_t		i;
	char		*itoa;

	num = n;
	i = counter(n);
	if (n < 0)
	{
		num *= -1;
		i++;
	}
	itoa = (char *)malloc((i + 1) * sizeof(char));
	if (!itoa)
		return (NULL);
	itoa[i] = 0;
	while (i)
	{
		i--;
		itoa[i] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		*itoa = '-';
	return (itoa);
}
// int	main(void)
// {
// 	int n;
// 	n = -2147483648;
// 	char *a = ft_itoa(n);
// 	printf("%s", a);
// }
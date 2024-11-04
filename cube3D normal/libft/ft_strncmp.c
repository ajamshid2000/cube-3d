/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 09:00:21 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/06 13:59:48 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (s1[i] == s2[i] && s1[i] && s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int	main(void)
// {
// 	char	s1[];
// 	char	s2[];
// 	int		result;
// 	int		result1;

// 	s1[] = "16,6";
// 	s2[] = "16,6";
// 	result = ft_strncmp(s1, s2, 6);
// 	result1 = strncmp(s1, s2, 6);
// 	printf("%i", result);
// 	printf("\n\n%i", result1);
// }

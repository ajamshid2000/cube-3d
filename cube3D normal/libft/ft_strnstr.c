/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:45:43 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/06 13:04:00 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	if (len == 0)
		return (0);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && big[i + j] && i
			+ j < len)
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char *str;
// 	char big[] = "kasjheldhfhelloa;lsdkfj";
// 	char little[] = "hello";
// 	int len = 4;
// 	char *dif = ft_strnstr(big, little, len);
// 	str = ft_strnstr("lorem ipsum dolor sit amet", "ipsum", 15);
// 	printf("%s", str);

// 	if (!(str = ft_strnstr("lorem ipsum dolor sit lorem ipsum dolor", "ipsum",
// 				35)))
// 		printf("NULL");
// 	else
// 		printf("%s", str);
// }
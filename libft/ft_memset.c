/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:09:22 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/01 12:27:12 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (n != i)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}

// int	main(void)
// {
// 	char			c[] = "alakdsf";
// 	char				i;
// 	unsigned int	n;

// 	i = 'b';
// 	n = 3;
// 	//ft_memset(c, i, n);
// 	memset(c, i, n);
// 	printf("%s", c);
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:35:39 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/01 12:26:17 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n != i)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

// int	main(void)
// {
// 	char			c[] = "alakdsf";
// 	unsigned int	n;

// 	n = 3;
// 	ft_bzero(c, n);
// 	//bzero(c, n);
// 	//printf("%s", c);
//     write(1, &c[3],1);
// 	return (0);
// }
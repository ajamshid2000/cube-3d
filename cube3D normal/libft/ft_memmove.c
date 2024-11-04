/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:46:02 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/07 10:41:08 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dest && !src)
		return (0);
	if (dest < src)
		while (++i < n)
			((char *)dest)[i] = ((char *)src)[i];
	if (dest > src)
		while (0 < n--)
			((char *)dest)[n] = ((char *)src)[n];
	return (dest);
}

// int	main(void)
// {
// 	char csrc[100] = "Geeksfor1";
//     char dest[100] = "hello world ";
// 	ft_memcpy(csrc, dest, 5);
// 	printf("%s\n", csrc);
// 	return (0);
// }
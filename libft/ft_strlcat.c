/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:01:58 by ajamshid          #+#    #+#             */
/*   Updated: 2023/11/20 11:10:24 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ln;

	if ((!dst || !src) && !size)
		return (0);
	i = 0;
	ln = ft_strlen(dst);
	if (size <= ln)
		return (size + ft_strlen(src));
	while (ln + i < (size - 1) && src[i])
	{
		dst[ln + i] = src[i];
		i++;
	}
	dst[ln + i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}

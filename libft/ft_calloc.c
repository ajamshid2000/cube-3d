/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:08:15 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/07 10:23:05 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*al_mem;

	if (nmemb > 0 && 2147483647 / nmemb < size)
		return (0);
	total = nmemb * size;
	al_mem = malloc(total);
	if (al_mem == NULL)
		return (0);
	ft_bzero(al_mem, total);
	return (al_mem);
}

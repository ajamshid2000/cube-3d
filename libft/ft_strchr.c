/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:58:45 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/07 10:10:04 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ss;
	unsigned char	cc;

	ss = (unsigned char *)s;
	cc = (unsigned char)c;
	while (*ss != '\0')
	{
		if (*ss == cc)
			return ((char *)ss);
		ss++;
	}
	if (*ss == cc)
		return ((char *)ss);
	if (c == 0)
		return ((char *)ss);
	return (NULL);
}

// int	main(void)
// {
// 	int c = 's';
// 	char s[] = "awergstartcc";
// 	char *n = ft_strchr(s, c);
// 	printf("%s", n);
// }
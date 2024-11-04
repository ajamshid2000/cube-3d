/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:49:07 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/01 12:29:17 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*ss;
	unsigned char	cc;

	i = 0;
	ss = (unsigned char *)s;
	cc = (unsigned char)c;
	while (ss[i])
		i++;
	while (i != -1)
	{
		if (ss[i] == cc)
		{
			return ((char *)(&ss[i]));
		}
		i--;
	}
	return (0);
}
// int	main(void)
// {
// 	int c = 's';
// 	char s[] = "sawergartccbs";
// 	char *n = ft_strrchr(s, c);
// 	printf("%s", n);
// }
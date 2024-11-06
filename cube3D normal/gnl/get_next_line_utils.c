/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:33:20 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/29 13:54:34 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_bzero(void *s)
{
	size_t	i;
	size_t	n;

	n = ft_strlen(s);
	i = 0;
	while (n != i)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*newstr;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = malloc(len);
	if (!newstr)
		return (NULL);
	i = -1;
	while (s1[++i])
		newstr[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	free((void *)s1);
	return (newstr);
}

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		i;

	if (!s)
		return (NULL);
	s2 = (char *)malloc(ft_strlen(s) + 1);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return ((char *)s2);
}

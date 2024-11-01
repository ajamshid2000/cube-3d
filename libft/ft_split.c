/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:35:45 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/17 13:18:16 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	no_words(char const *s, char c)
{
	int	n;

	n = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			n++;
		while (*s != c && *s)
			s++;
	}
	return (n);
}

static int	splitit(char const *s, int length, int i, char **splitted)
{
	splitted[i] = ft_substr(s, 0, length);
	if (!splitted[i])
	{
		while (i > 0)
		{
			i--;
			free(splitted[i]);
		}
		free(splitted);
		return (0);
	}
	i++;
	return (i);
}

static int	word_length(char const *s, char c)
{
	int	length;

	if (!ft_strchr(s, c))
		length = ft_strlen(s);
	else
		length = ft_strchr(s, c) - s;
	return (length);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	int		length;
	int		i;

	i = 0;
	splitted = (char **)malloc((no_words(s, c) + 1) * sizeof(char *));
	if (!s || !splitted)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			length = word_length(s, c);
			i = splitit(s, length, i, splitted);
			if (i == 0)
				return (NULL);
			s += length;
		}
	}
	splitted[i] = NULL;
	return (splitted);
}

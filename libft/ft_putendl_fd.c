/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:44:09 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/08 10:57:57 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	newline;

	newline = '\n';
	i = 0;
	while (s[i])
	{
		write(fd, (void *)&s[i], 1);
		i++;
	}
	write(fd, (void *)&newline, 1);
}

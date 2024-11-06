/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:27:58 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/29 15:06:45 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *stored, int i)
{
	int		j;
	char	*s;

	j = 0;
	s = ft_strdup(stored);
	ft_bzero(&s[i + 1]);
	while (stored[j + i + 1] != '\0')
	{
		stored[j] = stored[j + i + 1];
		j++;
	}
	ft_bzero(stored + j);
	return (s);
}

char	*ft_split_line(char **real_stored)
{
	int		i;
	char	*s;
	char	*stored;

	i = 0;
	if (!*real_stored || !real_stored)
		return (NULL);
	stored = *real_stored;
	if (!*stored)
		return (NULL);
	while (stored[i] != '\0' && stored[i] != '\n')
		i++;
	if (stored[i] == '\0' || (stored[i] == '\n' && stored[i + 1] == '\0'))
	{
		*real_stored = NULL;
		return (stored);
	}
	s = ft_line(stored, i);
	return (s);
}

char	*readlines(char *buffer, char **real_stored, int bytes_read, int fd)
{
	char	*s;

	while (bytes_read > 0)
	{
		buffer[bytes_read] = 0;
		*real_stored = ft_strjoin(*real_stored, buffer);
		if (ft_strchr(buffer, '\n'))
		{
			free(buffer);
			s = ft_split_line(&*real_stored);
			return (s);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (NULL);
}

int	check_fd(int fd, char **stored)
{
	int	bytes_read;

	bytes_read = read(fd, 0, 0);
	if (fd < 0 || BUFFER_SIZE <= 0 || bytes_read < 0)
	{
		if (*stored)
			free(*stored);
		*stored = NULL;
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*s;
	char		*buffer;
	int			bytes_read;

	bytes_read = check_fd(fd, &stored);
	if (!bytes_read)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		s = readlines(buffer, &stored, bytes_read, fd);
		if (s)
			return (s);
	}
	free(buffer);
	s = ft_split_line(&stored);
	return (s);
}

// int	main(void)
// {
// 	char	*s;
// 	int		fd;
// 	int		i;

// 	fd = open("text.txt", O_RDONLY);
// 	if (fd == -1)
// 		printf("cannot open the file");
// 	else
// 	{
// 		i = 0;
// 		while (i < 5)
// 		{
// 			s = get_next_line(fd);
// 			if (s)
// 				printf("printed %s", s);
// 			i++;
// 			if (s)
// 				free(s);
// 		}
// 	}
// 	close(fd);
// 	return (0);
// }

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 65
// # endif
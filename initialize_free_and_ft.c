/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_free_and_ft.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:00:57 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/10/31 13:11:11 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	free_table(char **table)
{
	int	i;

	i = 0;
	while (table && table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	return (0);
}

void	clean_exit(t_map *map)
{
	(void)map;
	close(map->cub_fd);
	if (map)
	{
		if (map->north_wall)
			free_table(map->north_wall);
		if (map->south_wall)
			free_table(map->south_wall);
		if (map->east_wall)
			free_table(map->east_wall);
		if (map->west_wall)
			free_table(map->west_wall);
		if (map->sky_color)
			free_table(map->sky_color);
		if (map->ground_color)
			free_table(map->ground_color);
		if (map->map)
			free(map->map);
		if (map->map_2d)
			free_table(map->map_2d);
	}
	exit(0);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		len;
	char	*newstr;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	newstr = malloc(len);
	if (!newstr)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		newstr[i] = s1[i];
	j = 0;
	while (s2 && s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	if (s1)
		free((void *)s1);
	newstr[i + j] = '\0';
	return (newstr);
}

int	ft_atoi_base(unsigned int decimal)
{
	int	hex;
	int	remainder;
	int	place;

	hex = 0;
	place = 1;
	while (decimal > 0)
	{
		remainder = decimal % 16;
		hex += remainder * place;
		decimal /= 16;
		place *= 16;
	}
	return (hex);
}

int	initialize_map(t_map *map, int fd)
{
	map->north_wall = NULL;
	map->south_wall = NULL;
	map->east_wall = NULL;
	map->west_wall = NULL;
	map->sky_color = NULL;
	map->ground_color = NULL;
	map->map = NULL;
	map->player_dir = 0;
	map->player_pos_x = 0;
	map->player_pos_y = 0;
	map->cub_fd = fd;
	return (0);
}

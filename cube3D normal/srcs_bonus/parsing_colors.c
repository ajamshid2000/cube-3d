/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:05:02 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/27 20:10:38 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

void	check_colors_range(char **sky, char **ground, t_map *map)
{
	if (!sky[0] || !sky[1] || !sky[2] || !ground[0] || !ground[1] || !ground[2])
	{
		ft_printf("Error\ncolors are not complete\n");
		free_table(sky);
		free_table(ground);
		clean_exit(map);
	}
	if (!((ft_atoi(sky[0]) < 256 && ft_atoi(sky[0]) > 0)
			|| (ft_atoi(sky[1]) < 256 && ft_atoi(sky[1]) > 0)
			|| (ft_atoi(sky[2]) < 256 && ft_atoi(sky[2]) > 0)
			|| (ft_atoi(ground[0]) < 256 && ft_atoi(ground[0]) > 0)
			|| (ft_atoi(ground[1]) < 256 && ft_atoi(ground[1]) > 0)
			|| (ft_atoi(ground[2]) < 256 && ft_atoi(ground[2]) > 0)))
	{
		ft_printf("Error\nnumber smaller than 255 ");
		ft_printf("or greater than 0 required in color");
		free_table(sky);
		free_table(ground);
		clean_exit(map);
	}
}

int	parse_colors(t_map *map)
{
	char	**sky;
	char	**ground;

	sky = ft_split(map->sky_color[0], ',');
	ground = ft_split(map->ground_color[0], ',');
	check_colors_range(sky, ground, map);
	map->sky_hexa = (ft_atoi(sky[0]) * 256 + ft_atoi(sky[1])) * 256
		+ ft_atoi(sky[2]);
	map->ground_hexa = (ft_atoi(ground[0]) * 256 + ft_atoi(ground[1])) * 256
		+ ft_atoi(ground[2]);
	free_table(sky);
	free_table(ground);
	return (0);
}

int	*map_count(t_map *map)
{
	int	i;
	int	j;
	int	*map_count;

	i = 0;
	while (map->map_2d[i])
		i++;
	map->map_height = i;
	map_count = (int *)malloc(sizeof(int) * i);
	if (!map_count)
		return (0);
	i = 0;
	while (map->map_2d[i])
	{
		j = 0;
		while (map->map_2d[i][j] && map->map_2d[i][j] != '\n')
			j++;
		map_count[i] = j - 1;
		i++;
	}
	return (map_count);
}

void	check_if_all_is_set(t_map *map)
{
	if ((!map->north_wall || !map->south_wall || !map->east_wall
			|| !map->west_wall || !map->sky_color || !map->ground_color
			|| !map->map_2d))
	{
		ft_printf("Error\nthe .cub file does not contain ");
		ft_printf("all of the neccessary info\n");
		clean_exit(map);
	}
}

void	check_if_map_is_surrounded(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map_2d[i])
	{
		j = 0;
		while (map->map_2d[i][j] && map->map_2d[i][j] == ' ')
			j++;
		if (map->map_2d[i][j] == '0')
		{
			ft_printf("Error\nmap is not closed\n");
			clean_exit(map);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_and_checking.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yand <mel-yand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:58:18 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/12/02 15:30:58 by mel-yand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	find(char **tab, int x, int y, t_map *map)
{
	int	i;

	i = 0;
	while (x >= 0 && tab[x] != NULL && tab[x][i])
		i++;
	if (x < 0 || tab[x] == NULL || y < 0 || y > i || tab[x][y] == '\0'
		|| tab[x][y] == '\n')
		return (1);
	if (tab[x][y] == '1')
		return (0);
	tab[x][y] = '1';
	if (find(tab, x - 1, y, map))
		return (1);
	if (find(tab, x + 1, y, map))
		return (1);
	if (find(tab, x, y - 1, map))
		return (1);
	if (find(tab, x, y + 1, map))
		return (1);
	return (0);
}

int	check_for_spawning_pos_and_dir(t_map *map, char **map_temp, int x)
{
	int	y;

	while (map->map_2d[x])
	{
		y = 0;
		while (map->map_2d[x][y])
		{
			if (map->map_2d[x][y] == 'N' || map->map_2d[x][y] == 'S'
				|| map->map_2d[x][y] == 'E' || map->map_2d[x][y] == 'W')
			{
				map->player_dir = map->map_2d[x][y];
				map->player_pos_x = x;
				map->player_pos_y = y;
				map->map_2d[x][y] = '0';
				break ;
			}
			y++;
		}
		if (map->player_dir)
			break ;
		x++;
	}
	if (map->map_2d[x])
		map_temp[x][y] = '0';
	return (x);
}

void	check_for_extra_characters_in_map(t_map *map, char **map_temp, int x,
		int y)
{
	x = 0;
	while (map_temp[x])
	{
		y = 0;
		while (map_temp[x][y])
		{
			if (map_temp[x][y] == ' ')
			{
				map_temp[x][y] = '1';
				map->map_2d[x][y] = '1';
			}
			if (!(map_temp[x][y] == '1' || map_temp[x][y] == ' '
					|| map_temp[x][y] == '0'))
			{
				ft_printf("Error\nthere is unwanted charecter in map area or ");
				ft_printf("more than on starting pos '%c'\n", map_temp[x][y]);
				free_table(map_temp);
				clean_exit(map);
			}
			y++;
		}
		x++;
	}
}

void	find_ground_and_check(t_map *map, int x, int y, char **map_temp)
{
	while (map_temp[x][y])
	{
		if (map_temp[map->player_pos_x][map->player_pos_y] != '1'
			|| map_temp[x][y] == '0')
		{
			if (map_temp[map->player_pos_x][map->player_pos_y] != '1')
			{
				if (find(map_temp, map->player_pos_x, map->player_pos_y, map))
				{
					printf("Error\nthere is/are ground not covered by walls\n");
					free_table(map_temp);
					clean_exit(map);
				}
			}
			else if (find(map_temp, x, y, map))
			{
				printf("Error\nthere is/are ground not covered by walls\n");
				free_table(map_temp);
				clean_exit(map);
			}
			x = 0;
			y = 0;
		}
		y++;
	}
}

int	check_player_spawning_pos(t_map *map)
{
	int		y;
	int		x;
	char	**map_temp;

	map->map_2d = ft_split(map->map, '\n');
	check_if_map_is_surrounded(map);
	map_temp = ft_split(map->map, '\n');
	x = check_for_spawning_pos_and_dir(map, map_temp, 0);
	if (!map->map_2d[x])
	{
		ft_printf("Error\npos not found, it must be N, S, E, or W\n");
		free_table(map_temp);
		clean_exit(map);
	}
	check_for_extra_characters_in_map(map, map_temp, 0, 0);
	x = 0;
	while (map_temp[x])
	{
		y = 0;
		find_ground_and_check(map, x, y, map_temp);
		x++;
	}
	free_table(map_temp);
	return (0);
}

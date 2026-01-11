/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yand <mel-yand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:06:07 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/12/06 14:57:24 by mel-yand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

int	initialize_map(t_map *map, int fd)
{
	map->north_wall = NULL;
	map->south_wall = NULL;
	map->east_wall = NULL;
	map->west_wall = NULL;
	map->sky_color = NULL;
	map->ground_color = NULL;
	map->map = NULL;
	map->map_2d = NULL;
	map->player_dir = 0;
	map->player_pos_x = 0;
	map->player_pos_y = 0;
	map->map_last = 0;
	map->cub_fd = fd;
	return (0);
}

void	init_player_dir(t_game *game, t_map *map)
{
	game->dir_x = 0;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0;
	if (map->player_dir == 'N')
	{
		game->dir_x = -1;
		game->plane_y = 0.66;
	}
	else if (map->player_dir == 'S')
	{
		game->dir_x = 1;
		game->plane_y = -0.66;
	}
	else if (map->player_dir == 'E')
	{
		game->dir_y = 1;
		game->plane_x = 0.66;
	}
	else if (map->player_dir == 'W')
	{
		game->dir_y = -1;
		game->plane_x = -0.66;
	}
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

void	initialize_game_vars(t_game *game, t_map *map)
{
	game->wall_tex[0].img_ptr = NULL;
	game->wall_tex[1].img_ptr = NULL;
	game->wall_tex[2].img_ptr = NULL;
	game->wall_tex[3].img_ptr = NULL;
	game->img.img_ptr = NULL;
	game->win_ptr = NULL;
	game->mlx_ptr = NULL;
	game->esc = 0;
	game->map_structure = map;
	game->map = map->map_2d;
	game->sky_color = map->sky_hexa;
	game->ground_color = map->ground_hexa;
	game->player_x = map->player_pos_x + 0.5;
	game->player_y = map->player_pos_y + 0.5;
	ft_memset(game->keys, 0, sizeof(game->keys));
	init_player_dir(game, map);
	game->map_co = map_count(game->map_structure);
	if (!game->map_co)
		clean_exit(map);
}

void	set_initial_values(t_raycasting *raycasting, t_game *game, int x)
{
	double	screen_cord;

	screen_cord = 2 * x / (double)SCREEN_WIDTH - 1;
	raycasting->ray_dir_x = game->dir_x + game->plane_x * screen_cord;
	raycasting->ray_dir_y = game->dir_y + game->plane_y * screen_cord;
	raycasting->map_x = (int)game->player_x;
	raycasting->map_y = (int)game->player_y;
	raycasting->dist_between_x = fabs(1 / raycasting->ray_dir_x);
	raycasting->dist_between_y = fabs(1 / raycasting->ray_dir_y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:06:07 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/04 01:19:01 by abdul-rashe      ###   ########.fr       */
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
	map->player_dir = 0;
	map->player_pos_x = 0;
	map->player_pos_y = 0;
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

void	initialize_game_vars(t_game *game, t_map *map)
{
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

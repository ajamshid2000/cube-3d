/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:13:32 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/26 19:25:18 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

void	check_texture_init_success(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->wall_tex[i].img_ptr)
		{
			printf("Error loading texture,please make sure the name is ");
			printf("correct or there are not spaces after the adress %i\n", i);
			destroy_image_and_clean_exit(game);
		}
		game->wall_tex[i].data = mlx_get_data_addr(game->wall_tex[i].img_ptr,
				&game->wall_tex[i].bpp, &game->wall_tex[i].size_line,
				&game->wall_tex[i].endian);
		i++;
	}
}

void	load_textures(t_game *game, t_map *map)
{
	game->wall_tex[0].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			map->north_wall[0], &game->wall_tex[0].width,
			&game->wall_tex[0].height);
	game->wall_tex[1].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			map->south_wall[0], &game->wall_tex[1].width,
			&game->wall_tex[1].height);
	game->wall_tex[2].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			map->west_wall[0], &game->wall_tex[2].width,
			&game->wall_tex[2].height);
	game->wall_tex[3].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			map->east_wall[0], &game->wall_tex[3].width,
			&game->wall_tex[3].height);
	check_texture_init_success(game);
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

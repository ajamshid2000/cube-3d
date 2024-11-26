/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:32:52 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/24 16:53:35 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

void	set_pixel_color(t_game *game, int x, int y, int color)
{
	int	pixel_offset;

	pixel_offset = y * game->img.size_line + x * (game->img.bpp / 8);
	game->img.data[pixel_offset] = (color & 0xFF);
	game->img.data[pixel_offset + 1] = (color >> 8) & 0xFF;
	game->img.data[pixel_offset + 2] = (color >> 16) & 0xFF;
	game->img.data[pixel_offset + 3] = (color >> 24) & 0xFF;
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
			printf("correct or there are not spaces after the adress\n");
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

void	set_distance_to_next_x_or_y(t_raycasting *raycasting, t_game *game)
{
	if (raycasting->ray_dir_x < 0)
	{
		raycasting->step_x = -1;
		raycasting->side_dest_x = (game->player_x - raycasting->map_x)
			* raycasting->dist_between_x;
	}
	else
	{
		raycasting->step_x = 1;
		raycasting->side_dest_x = (raycasting->map_x + 1.0 - game->player_x)
			* raycasting->dist_between_x;
	}
	if (raycasting->ray_dir_y < 0)
	{
		raycasting->step_y = -1;
		raycasting->side_dest_y = (game->player_y - raycasting->map_y)
			* raycasting->dist_between_y;
	}
	else
	{
		raycasting->step_y = 1;
		raycasting->side_dest_y = (raycasting->map_y + 1.0 - game->player_y)
			* raycasting->dist_between_y;
	}
}

void	find_wall_line_height_and_dist(t_raycasting *raycasting, t_game *game,
		int side)
{
	if (side == 0)
		raycasting->wall_dist = (raycasting->map_x - game->player_x + (1
					- raycasting->step_x) / 2) / raycasting->ray_dir_x;
	else
		raycasting->wall_dist = (raycasting->map_y - game->player_y + (1
					- raycasting->step_y) / 2) / raycasting->ray_dir_y;
	raycasting->line_height = (int)(SCREEN_HEIGHT / raycasting->wall_dist);
}

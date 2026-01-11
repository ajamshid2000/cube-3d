/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:21:52 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/03 22:38:42 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	find_wall_side_dist_and_height(t_raycasting *raycasting, t_game *game)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (raycasting->side_dest_x < raycasting->side_dest_y)
		{
			raycasting->side_dest_x += raycasting->dist_between_x;
			raycasting->map_x += raycasting->step_x;
			side = 0;
		}
		else
		{
			raycasting->side_dest_y += raycasting->dist_between_y;
			raycasting->map_y += raycasting->step_y;
			side = 1;
		}
		if (game->map[raycasting->map_x][raycasting->map_y] > '0')
			hit = 1;
	}
	return (side);
}

void	prepare_writing_to_img(t_game *game, t_raycasting *raycasting,
		int tex_x, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < raycasting->draw_start)
			set_pixel_color(game, x, y, game->sky_color);
		if (y >= raycasting->draw_start && y <= raycasting->draw_end)
		{
			tex_y = (((y * 2 - SCREEN_HEIGHT + raycasting->line_height) / 2
						* raycasting->tex->height) / raycasting->line_height);
			color = *(int *)(raycasting->tex->data + (tex_y
						* raycasting->tex->size_line + tex_x
						* (raycasting->tex->bpp / 8)));
			set_pixel_color(game, x, y, color);
		}
		if (y > raycasting->draw_end)
			set_pixel_color(game, x, y, game->ground_color);
		y++;
	}
}

void	cast_rays_and_generate_image(t_game *game, t_raycasting *raycasting)
{
	int		tex_x;
	double	wall_width;
	int		x;
	int		side;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		set_initial_values(raycasting, game, x);
		set_distance_to_next_x_or_y(raycasting, game);
		side = find_wall_side_dist_and_height(raycasting, game);
		find_wall_line_height_and_dist(raycasting, game, side);
		wall_width = find_draw_pos_wall_width(raycasting, game, side);
		raycasting->tex = &game->wall_tex[find_tex_index(raycasting, side)];
		tex_x = (int)(wall_width * (double)raycasting->tex->width);
		if (side == 0 && raycasting->ray_dir_x > 0)
			tex_x = game->wall_tex[0].width - tex_x - 1;
		if (side == 1 && raycasting->ray_dir_y < 0)
			tex_x = game->wall_tex[0].width - tex_x - 1;
		prepare_writing_to_img(game, raycasting, tex_x, x);
		x++;
	}
}

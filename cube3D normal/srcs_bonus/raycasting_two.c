/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:33:11 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/17 14:18:37 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

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

double	find_draw_pos_wall_width(t_raycasting *raycasting, t_game *game,
		int side)
{
	double	wall_width;

	(void)side;
	raycasting->draw_start = (-raycasting->line_height + SCREEN_HEIGHT) / 2
		+ (int)(raycasting->wall_dist + raycasting->line_height / 5)
		* game->move_level / 2;
	if (raycasting->draw_start < 0)
		raycasting->draw_start = 0;
	raycasting->draw_end = (raycasting->line_height + SCREEN_HEIGHT) / 2
		+ (int)(raycasting->wall_dist + raycasting->line_height / 5)
		* game->move_level / 2;
	if (raycasting->draw_end >= SCREEN_HEIGHT)
		raycasting->draw_end = SCREEN_HEIGHT - 1;
	if (side == 0)
		wall_width = game->player_y + raycasting->wall_dist
			* raycasting->ray_dir_y;
	else
		wall_width = game->player_x + raycasting->wall_dist
			* raycasting->ray_dir_x;
	wall_width -= floor(wall_width);
	return (wall_width);
}

int	find_tex_index(t_raycasting *raycasting, int side)
{
	int	tex_index;

	if (side == 0)
	{
		if (raycasting->ray_dir_x > 0)
			tex_index = 1;
		else
			tex_index = 0;
	}
	else
	{
		if (raycasting->ray_dir_y > 0)
			tex_index = 3;
		else
			tex_index = 2;
	}
	return (tex_index);
}

void	draw_sky_and_ground(t_game *game, t_raycasting *raycasting, int y,
		int x)
{
	if (y < raycasting->draw_start)
		set_pixel_color(game, x, y, game->sky_color);
	if (y > raycasting->draw_end)
		set_pixel_color(game, x, y, game->ground_color);
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
		draw_sky_and_ground(game, raycasting, y, x);
		if (y >= raycasting->draw_start && y <= raycasting->draw_end)
		{
			tex_y = (((y * 2 - SCREEN_HEIGHT - (raycasting->wall_dist
								+ raycasting->line_height / 5)
							* game->move_level + raycasting->line_height) / 2)
					* raycasting->tex->height / raycasting->line_height);
			if (tex_y > raycasting->tex->height)
				tex_y = raycasting->tex->height;
			if (tex_y < 0)
				tex_y = 0;
			color = *(int *)(raycasting->tex->data + ((tex_y)
						* (raycasting->tex->size_line) + tex_x * 4));
			set_pixel_color(game, x, y, color);
		}
		y++;
	}
}

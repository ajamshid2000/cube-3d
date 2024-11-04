/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:22:54 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/03 22:38:48 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	find_draw_pos_wall_width(t_raycasting *raycasting, t_game *game,
		int side)
{
	double	wall_width;

	raycasting->draw_start = (-raycasting->line_height + SCREEN_HEIGHT) / 2;
	if (raycasting->draw_start < 0)
		raycasting->draw_start = 0;
	raycasting->draw_end = (raycasting->line_height + SCREEN_HEIGHT) / 2;
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

void	set_pixel_color(t_game *game, int x, int y, int color)
{
	int	pixel_offset;

	pixel_offset = y * game->img.size_line + x * (game->img.bpp / 8);
	game->img.data[pixel_offset] = (color & 0xFF);
	game->img.data[pixel_offset + 1] = (color >> 8) & 0xFF;
	game->img.data[pixel_offset + 2] = (color >> 16) & 0xFF;
	game->img.data[pixel_offset + 3] = (color >> 24) & 0xFF;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:08:29 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/03 16:11:46 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_back_or_forward(t_game *game, double move_speed)
{
	if (game->keys[119])
	{
		if (game->map[(int)(game->player_x + game->dir_x * (2
					* move_speed))][(int)game->player_y] == '0')
			game->player_x += game->dir_x * (1 * move_speed);
		if (game->map[(int)game->player_x][(int)(game->player_y + game->dir_y
			* (2 * move_speed))] == '0')
			game->player_y += game->dir_y * (1 * move_speed);
	}
	if (game->keys[115])
	{
		if (game->map[(int)(game->player_x - game->dir_x * (2
					* move_speed))][(int)game->player_y] == '0')
			game->player_x -= game->dir_x * (1 * move_speed);
		if (game->map[(int)game->player_x][(int)(game->player_y - game->dir_y
			* (2 * move_speed))] == '0')
			game->player_y -= game->dir_y * (1 * move_speed);
	}
}

void	move_left_or_right(t_game *game, double move_speed)
{
	if (game->keys[97])
		if (game->map[(int)(game->player_x + (game->dir_x * cos(M_PI / 2)
					- game->dir_y * sin(M_PI / 2)) * (2
					* move_speed))][(int)game->player_y] == '0')
			game->player_x += (game->dir_x * cos(M_PI / 2) - game->dir_y
					* sin(M_PI / 2)) * (1 * move_speed);
	if (game->keys[97])
		if (game->map[(int)game->player_x][(int)(game->player_y + (game->dir_x
				* sin(M_PI / 2) + game->dir_y * cos(M_PI / 2)) * (2
				* move_speed))] == '0')
			game->player_y += (game->dir_x * sin(M_PI / 2) + game->dir_y
					* cos(M_PI / 2)) * (1 * move_speed);
	if (game->keys[100])
		if (game->map[(int)(game->player_x + (game->dir_x * cos(-M_PI / 2)
					- game->dir_y * sin(-M_PI / 2)) * (2
					* move_speed))][(int)game->player_y] == '0')
			game->player_x += (game->dir_x * cos(-M_PI / 2) - game->dir_y
					* sin(-M_PI / 2)) * (1 * move_speed);
	if (game->keys[100])
		if (game->map[(int)game->player_x][(int)(game->player_y + (game->dir_x
				* sin(-M_PI / 2) + game->dir_y * cos(-M_PI / 2)) * (2
				* move_speed))] == '0')
			game->player_y += (game->dir_x * sin(-M_PI / 2) + game->dir_y
					* cos(-M_PI / 2)) * (1 * move_speed);
}

void	turn_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.05;
	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
	game->dir_y = old_dir_x * sin(rot_speed) + game->dir_y * cos(rot_speed);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y
		* sin(rot_speed);
	game->plane_y = old_plane_x * sin(rot_speed) + game->plane_y
		* cos(rot_speed);
}

void	turn_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.05;
	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(-rot_speed) - game->dir_y * sin(-rot_speed);
	game->dir_y = old_dir_x * sin(-rot_speed) + game->dir_y * cos(-rot_speed);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(-rot_speed) - game->plane_y
		* sin(-rot_speed);
	game->plane_y = old_plane_x * sin(-rot_speed) + game->plane_y
		* cos(-rot_speed);
}

void	move_player(t_game *game)
{
	double	move_speed;

	move_speed = 0.1;
	if (game->keys[119] || game->keys[115])
		move_back_or_forward(game, move_speed);
	if (game->keys[97] || game->keys[100])
		move_left_or_right(game, move_speed);
	if (game->keys[1])
		turn_left(game);
	if (game->keys[0])
		turn_right(game);
}

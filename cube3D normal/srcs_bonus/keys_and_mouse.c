/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_and_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:50:14 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/27 20:21:59 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

void	turning_and_sprite(t_game *game, int a)
{
	static int	move_times = 1;
	static int	move_dir = 1;

	if (a < 0 || game->keys[1])
		turn_left(game, fabs((double)a / 90.0));
	if (a > 0 || game->keys[0])
		turn_right(game, fabs((double)a / 90.0));
	if (game->keys[97] || game->keys[100] || game->keys[119] || game->keys[115])
	{
		if (move_times == 8)
			move_dir = -1;
		if (move_times == 1)
			move_dir = 1;
		if (move_dir == -1)
			move_times--;
		if (move_dir == 1)
			move_times++;
	}
	game->move_level = (double)move_times / 9;
}

void	move_player(t_game *game)
{
	double	move_speed;
	int		a;
	int		b;
	int		i;

	i = 0;
	a = 0;
	if (!game->esc)
	{
		while (!a)
		{
			mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &a, &b);
			a = a - 400;
			if (i == 300)
				break ;
			i++;
		}
	}
	move_speed = 0.05;
	if (game->keys[119] || game->keys[115])
		move_back_or_forward(game, move_speed);
	if (game->keys[97] || game->keys[100])
		move_left_or_right(game, move_speed);
	turning_and_sprite(game, a);
}

int	key_press(int key, t_game *game)
{
	if (key < 1024)
		game->keys[key] = 1;
	if (key == 65363)
		game->keys[0] = 1;
	if (key == 65361)
		game->keys[1] = 1;
	if (key == 65307)
	{
		if (game->esc == 0)
		{
			game->esc = 1;
			mlx_mouse_show(game->mlx_ptr, game->win_ptr);
		}
		else
			destroy_image_and_clean_exit(game);
	}
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key < 1024)
		game->keys[key] = 0;
	if (key == 65363)
		game->keys[0] = 0;
	if (key == 65361)
		game->keys[1] = 0;
	return (0);
}

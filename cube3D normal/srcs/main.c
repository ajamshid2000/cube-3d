/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:04:47 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/03 16:37:10 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key_press(int key, t_game *game)
{
	if (key < 1024)
		game->keys[key] = 1;
	if (key == 65363)
		game->keys[0] = 1;
	if (key == 65361)
		game->keys[1] = 1;
	if (key == 65307)
		destroy_image_and_clean_exit(game);
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

int	main_loop(t_game *game)
{
	t_raycasting	raycasting;

	move_player(game);
	cast_rays_and_generate_image(game, &raycasting);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0,
		0);
	usleep(20000);
	return (0);
}

int	main(void)
{
	t_map	map;
	t_game	game;

	parse_cub_file(&map, "./map.cub");
	game.map_structure = &map;
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"CUBE 3D");
	game.img.img_ptr = mlx_new_image(game.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img.data = mlx_get_data_addr(game.img.img_ptr, &game.img.bpp,
			&game.img.size_line, &game.img.endian);
	load_textures(&game, &map);
	game.map = map.map_2d;
	game.sky_color = map.sky_hexa;
	game.ground_color = map.ground_hexa;
	game.player_x = map.player_pos_x + 0.5;
	game.player_y = map.player_pos_y + 0.5;
	init_player_dir(&game, &map);
	ft_memset(game.keys, 0, sizeof(game.keys));
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_hook(game.win_ptr, 17, 0, destroy_image_and_clean_exit, &game);
	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}

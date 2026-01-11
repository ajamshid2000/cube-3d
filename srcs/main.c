/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yand <mel-yand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:04:47 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/12/02 13:37:26 by mel-yand         ###   ########.fr       */
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

void	initialize_game_vars(t_game *game, t_map *map)
{
	game->wall_tex[0].img_ptr = NULL;
	game->wall_tex[1].img_ptr = NULL;
	game->wall_tex[2].img_ptr = NULL;
	game->wall_tex[3].img_ptr = NULL;
	game->img.img_ptr = NULL;
	game->win_ptr = NULL;
	game->mlx_ptr = NULL;
	game->map_structure = map;
	game->map = map->map_2d;
	game->sky_color = map->sky_hexa;
	game->ground_color = map->ground_hexa;
	game->player_x = map->player_pos_x + 0.5;
	game->player_y = map->player_pos_y + 0.5;
	ft_memset(game->keys, 0, sizeof(game->keys));
	init_player_dir(game, map);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;

	if (argc != 2)
		return (ft_printf("Error\ninvalid number argument\n"));
	parse_cub_file(&map, argv[1]);
	initialize_game_vars(&game, &map);
	init_mlx_components(&game);
	load_textures(&game, &map);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_hook(game.win_ptr, 17, 0, destroy_image_and_clean_exit, &game);
	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}

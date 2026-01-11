/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yand <mel-yand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:04:47 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/12/02 13:37:56 by mel-yand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

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
			tex_x = raycasting->tex->width - tex_x - 1;
		if (side == 1 && raycasting->ray_dir_y < 0)
			tex_x = raycasting->tex->width - tex_x - 1;
		prepare_writing_to_img(game, raycasting, tex_x, x);
		x++;
	}
}

void	calculate_and_draw_minimap(t_game *game, double x, double y,
		double cam_x)
{
	double	cam_y;
	double	i;
	double	j;

	cam_x = 2 * (x) / 192.0 - 1;
	while (y < SCREEN_HEIGHT)
	{
		cam_y = 2 * (SCREEN_HEIGHT - y) / 192.0 - 1;
		cam_y = -1.0 * cam_y;
		i = game->player_x + 8 * cam_y;
		j = game->player_y + 8 * cam_x;
		if ((int)i < 0 || (int)j < 0
			|| (int)i > (game->map_structure->map_height - 1)
			|| (int)j > game->map_co[(int)i] || ((int)((i - game->player_x) * (i
					- game->player_x) * 15 + (j - game->player_y) * (j
					- game->player_y) * 15) == 1))
			set_pixel_color(game, x, y, 0x0);
		else if (game->map[(int)i][(int)j] == '1')
			set_pixel_color(game, x, y, 0xffffff);
		else if (game->map[(int)i][(int)j] == '0')
			set_pixel_color(game, x, y, 0x00ff00);
		else
			set_pixel_color(game, x, y, 0x0);
		y++;
	}
}

int	main_loop(t_game *game)
{
	t_raycasting	raycasting;
	double			x;
	double			y;

	move_player(game);
	if (!game->esc)
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, SCREEN_HEIGHT / 2,
			SCREEN_WIDTH / 2);
	cast_rays_and_generate_image(game, &raycasting);
	x = 0;
	y = SCREEN_HEIGHT - 192;
	while (x < 192)
	{
		calculate_and_draw_minimap(game, x, y, 0.0);
		x++;
	}
	x = 0;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0,
		0);
	usleep(10000);
	return (0);
}

void	init_mlx_components(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		destroy_image_and_clean_exit(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"CUBE 3D");
	if (!game->win_ptr)
		destroy_image_and_clean_exit(game);
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!game->img.img_ptr)
		destroy_image_and_clean_exit(game);
	game->img.data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.size_line, &game->img.endian);
	if (!game->img.data)
		destroy_image_and_clean_exit(game);
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
	mlx_mouse_move(game.mlx_ptr, game.win_ptr, SCREEN_HEIGHT / 2, SCREEN_WIDTH
		/ 2);
	mlx_mouse_hide(game.mlx_ptr, game.win_ptr);
	load_textures(&game, &map);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_hook(game.win_ptr, 17, 0, destroy_image_and_clean_exit, &game);
	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
/*after 		find_wall_line_height_and_dist(raycasting, game, side);
		I CAN USE THIS TO OPEN OR CLOSE A DOOR OR I SHOULD LOOK AROUND THE PLAYER
		TO SEE IF IT IS ONE BLOCK NEAR ANY DOOR IF IT WAS I CAN SET THE DOOR TO 3
		TO KNOW THAT THE DOOR IS OPEN AND IT CAN BE COUNTED AS GROUND AREA
		// if(hit == 1 && raycasting->wall_dist < 1)
		// 	game->map[raycasting->map_x][raycasting->map_y] ='0';*/
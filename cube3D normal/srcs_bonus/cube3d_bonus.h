/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:26:34 by ajamshid          #+#    #+#             */
/*   Updated: 2024/11/27 20:09:14 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_BONUS_H
# define CUBE3D_BONUS_H

# include "ft_printf.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

typedef struct s_texture
{
	void		*img_ptr;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_image
{
	void		*img_ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct s_map
{
	char		**north_wall;
	char		**south_wall;
	char		**east_wall;
	char		**west_wall;

	char		**sky_color;
	char		**ground_color;
	int			sky_hexa;
	int			ground_hexa;

	char		*map;
	char		**map_2d;
	int			map_height;

	char		player_dir;
	int			player_pos_x;
	int			player_pos_y;

	int			map_last;

	int			cub_fd;

}				t_map;

typedef struct s_raycasting
{
	double		ray_dir_y;
	double		ray_dir_x;

	int			map_x;
	int			map_y;

	double		dist_between_x;
	double		dist_between_y;
	double		side_dest_x;
	double		side_dest_y;

	int			step_x;
	int			step_y;

	double		wall_dist;
	double		wall_width;
	int			line_height;

	int			draw_start;
	int			draw_end;
	t_texture	*tex;

}				t_raycasting;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			keys[1024];
	char		**map;
	int			map2[MAP_WIDTH][MAP_HEIGHT];
	int			sky_color;
	int			ground_color;
	double		move_level;
	int			esc;
	int			*map_co;
	int			mouse_x;
	int			mouse_y;

	t_texture	wall_tex[4];
	t_image		img;
	t_map		*map_structure;
}				t_game;

int				parse_cub_file(t_map *map, char *map_cub);
char			*get_next_line(int fd);
void			clean_exit(t_map *map);
int				free_table(char **table);
char			*ft_strjoin_free(char const *s1, char const *s2);
int				initialize_map(t_map *map, int fd);
void			check_if_map_is_surrounded(t_map *map);
int				check_player_spawning_pos(t_map *map);
int				parse_colors(t_map *map);
int				*map_count(t_map *map);
void			initialize_game_vars(t_game *game, t_map *map);
int				destroy_image_and_clean_exit(t_game *game);
void			init_player_dir(t_game *game, t_map *map);
void			move_player(t_game *game);
void			set_initial_values(t_raycasting *raycasting, t_game *game,
					int x);
int				key_press(int key, t_game *game);
int				key_release(int key, t_game *game);
void			move_back_or_forward(t_game *game, double move_speed);
void			move_left_or_right(t_game *game, double move_speed);
void			turn_left(t_game *game, double rot_s);
void			turn_right(t_game *game, double rot_s);
void			set_pixel_color(t_game *game, int x, int y, int color);
void			check_texture_init_success(t_game *game);
void			load_textures(t_game *game, t_map *map);
void			set_distance_to_next_x_or_y(t_raycasting *raycasting,
					t_game *game);
void			find_wall_line_height_and_dist(t_raycasting *raycasting,
					t_game *game, int side);
int				find_wall_side_dist_and_height(t_raycasting *raycasting,
					t_game *game);
double			find_draw_pos_wall_width(t_raycasting *raycasting, t_game *game,
					int side);
int				find_tex_index(t_raycasting *raycasting, int side);
void			prepare_writing_to_img(t_game *game, t_raycasting *raycasting,
					int tex_x, int x);
void			check_if_all_is_set(t_map *map);

#endif

// #include "cube3d.h"

// void	set_pixel_color(t_game *game, int x, int y, int color)
// {
// 	int	pixel_offset;

// 	pixel_offset = y * game->img.size_line + x * (game->img.bpp / 8);
// 	game->img.data[pixel_offset] = (color & 0xFF);
// 	game->img.data[pixel_offset + 1] = (color >> 8) & 0xFF;
// 	game->img.data[pixel_offset + 2] = (color >> 16) & 0xFF;
// 	game->img.data[pixel_offset + 3] = (color >> 24) & 0xFF;
// }

// void	move_back_or_forward(t_game *game, double move_speed)
// {
// 	if (game->keys[119])
// 	{
// 		if (game->map[(int)(game->player_x + game->dir_x * (2
// 					* move_speed))][(int)game->player_y] == '0')
// 			game->player_x += game->dir_x * (1 * move_speed);
// 		if (game->map[(int)game->player_x][(int)(game->player_y + game->dir_y
// 				* (2 * move_speed))] == '0')
// 			game->player_y += game->dir_y * (1 * move_speed);
// 	}
// 	if (game->keys[115])
// 	{
// 		if (game->map[(int)(game->player_x - game->dir_x * (2
// 					* move_speed))][(int)game->player_y] == '0')
// 			game->player_x -= game->dir_x * (1 * move_speed);
// 		if (game->map[(int)game->player_x][(int)(game->player_y - game->dir_y
// 				* (2 * move_speed))] == '0')
// 			game->player_y -= game->dir_y * (1 * move_speed);
// 	}
// }

// void	move_left_or_right(t_game *game, double move_speed)
// {
// 	if (game->keys[97])
// 		if (game->map[(int)(game->player_x + (game->dir_x * cos(M_PI / 2)
// 					- game->dir_y * sin(M_PI / 2)) * (2
// 					* move_speed))][(int)game->player_y] == '0')
// 			game->player_x += (game->dir_x * cos(M_PI / 2) - game->dir_y
// 					* sin(M_PI / 2)) * (1 * move_speed);
// 	if (game->keys[97])
// 		if (game->map[(int)game->player_x][(int)(game->player_y + (game->dir_x
// 					* sin(M_PI / 2) + game->dir_y * cos(M_PI / 2)) * (2
// 					* move_speed))] == '0')
// 			game->player_y += (game->dir_x * sin(M_PI / 2) + game->dir_y
// 					* cos(M_PI / 2)) * (1 * move_speed);
// 	if (game->keys[100])
// 		if (game->map[(int)(game->player_x + (game->dir_x * cos(-M_PI / 2)
// 					- game->dir_y * sin(-M_PI / 2)) * (2
// 					* move_speed))][(int)game->player_y] == '0')
// 			game->player_x += (game->dir_x * cos(-M_PI / 2) - game->dir_y
// 					* sin(-M_PI / 2)) * (1 * move_speed);
// 	if (game->keys[100])
// 		if (game->map[(int)game->player_x][(int)(game->player_y + (game->dir_x
// 					* sin(-M_PI / 2) + game->dir_y * cos(-M_PI / 2)) * (2
// 					* move_speed))] == '0')
// 			game->player_y += (game->dir_x * sin(-M_PI / 2) + game->dir_y
// 					* cos(-M_PI / 2)) * (1 * move_speed);
// }

// void	turn_left(t_game *game, double rot_s)
// {
// 	double	old_dir_x;
// 	double	old_plane_x;
// 	double	rot_speed;

// 	if (rot_s)
// 		rot_speed = rot_s;
// 	else
// 		rot_speed = 0.05;
// 	old_dir_x = game->dir_x;
// 	game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
// 	game->dir_y = old_dir_x * sin(rot_speed) + game->dir_y * cos(rot_speed);
// 	old_plane_x = game->plane_x;
// 	game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y
// 		* sin(rot_speed);
// 	game->plane_y = old_plane_x * sin(rot_speed) + game->plane_y
// 		* cos(rot_speed);
// }

// void	turn_right(t_game *game, double rot_s)
// {
// 	double	old_dir_x;
// 	double	old_plane_x;
// 	double	rot_speed;

// 	if (rot_s)
// 		rot_speed = rot_s;
// 	else
// 		rot_speed = 0.05;
// 	old_dir_x = game->dir_x;
// 	game->dir_x = game->dir_x * cos(-rot_speed) - game->dir_y * sin(-rot_speed);
// 	game->dir_y = old_dir_x * sin(-rot_speed) + game->dir_y * cos(-rot_speed);
// 	old_plane_x = game->plane_x;
// 	game->plane_x = game->plane_x * cos(-rot_speed) - game->plane_y
// 		* sin(-rot_speed);
// 	game->plane_y = old_plane_x * sin(-rot_speed) + game->plane_y
// 		* cos(-rot_speed);
// }

// void	move_player(t_game *game)
// {
// 	double		move_speed;
// 	static int	move_times = 1;
// 	static int	move_dir = 1;
// 	int			a;
// 	int			b;

// 	if (!game->esc)
// 	{
// 		mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &a, &b);
// 		a = a - 400;
// 	}
// 	else
// 		a = 0;
// 	move_speed = 0.05;
// 	if (game->keys[119] || game->keys[115])
// 		move_back_or_forward(game, move_speed);
// 	if (game->keys[97] || game->keys[100])
// 		move_left_or_right(game, move_speed);
// 	if (a < 0 || game->keys[1])
// 		turn_left(game, fabs((double)a) / 100);
// 	if (a > 0 || game->keys[0] )
// 		turn_right(game, fabs((double)a) / 100);
// 	if (game->keys[97] || game->keys[100] || game->keys[119] || game->keys[115])
// 	{
// 		if (move_times == 8)
// 			move_dir = -1;
// 		if (move_times == 1)
// 			move_dir = 1;
// 		if (move_dir == -1)
// 			move_times--;
// 		if (move_dir == 1)
// 			move_times++;
// 		game->move_level = (double)move_times / 9;
// 		printf("%f\n", game->move_level);
// 	}
// }

// int	destroy_image_and_clean_exit(t_game *game)
// {
// 	if (game->wall_tex[0].img_ptr)
// 		mlx_destroy_image(game->mlx_ptr, game->wall_tex[0].img_ptr);
// 	if (game->wall_tex[1].img_ptr)
// 		mlx_destroy_image(game->mlx_ptr, game->wall_tex[1].img_ptr);
// 	if (game->wall_tex[2].img_ptr)
// 		mlx_destroy_image(game->mlx_ptr, game->wall_tex[2].img_ptr);
// 	if (game->wall_tex[3].img_ptr)
// 		mlx_destroy_image(game->mlx_ptr, game->wall_tex[3].img_ptr);
// 	if (game->img.img_ptr)
// 		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
// 	if (game->win_ptr)
// 		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
// 	if (game->mlx_ptr)
// 		mlx_destroy_display(game->mlx_ptr);
// 	if (game->mlx_ptr)
// 		free(game->mlx_ptr);
// 	clean_exit(game->map_structure);
// 	return (0);
// }

// int	key_press(int key, t_game *game)
// {
// 	if (key < 1024)
// 		game->keys[key] = 1;
// 	if (key == 65363)
// 		game->keys[0] = 1;
// 	if (key == 65361)
// 		game->keys[1] = 1;
// 	if (key == 65307)
// 	{
// 		if (game->esc == 0)
// 		{
// 			game->esc = 1;
// 			mlx_mouse_show(game->mlx_ptr, game->win_ptr);
// 		}
// 		else
// 			destroy_image_and_clean_exit(game);
// 	}
// 	return (0);
// }

// int	key_release(int key, t_game *game)
// {
// 	if (key < 1024)
// 		game->keys[key] = 0;
// 	if (key == 65363)
// 		game->keys[0] = 0;
// 	if (key == 65361)
// 		game->keys[1] = 0;
// 	return (0);
// }

// void	check_texture_init_success(t_game *game)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		if (!game->wall_tex[i].img_ptr)
// 		{
// 			printf("Error loading texture,please make sure the name is ");
// 			ft_printf("correct or there are not spaces after the adress\n");
// 			destroy_image_and_clean_exit(game);
// 		}
// 		game->wall_tex[i].data = mlx_get_data_addr(game->wall_tex[i].img_ptr,
// 				&game->wall_tex[i].bpp, &game->wall_tex[i].size_line,
// 				&game->wall_tex[i].endian);
// 		i++;
// 	}
// }

// void	load_textures(t_game *game, t_map *map)
// {
// 	game->wall_tex[0].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
// 			map->north_wall[0], &game->wall_tex[0].width,
// 			&game->wall_tex[0].height);
// 	game->wall_tex[1].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
// 			map->south_wall[0], &game->wall_tex[1].width,
// 			&game->wall_tex[1].height);
// 	game->wall_tex[2].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
// 			map->west_wall[0], &game->wall_tex[2].width,
// 			&game->wall_tex[2].height);
// 	game->wall_tex[3].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
// 			map->east_wall[0], &game->wall_tex[3].width,
// 			&game->wall_tex[3].height);
// 	check_texture_init_success(game);
// }

// void	set_initial_values(t_raycasting *raycasting, t_game *game, int x)
// {
// 	double	screen_cord;

// 	screen_cord = 2 * x / (double)SCREEN_WIDTH - 1;
// 	raycasting->ray_dir_x = game->dir_x + game->plane_x * screen_cord;
// 	raycasting->ray_dir_y = game->dir_y + game->plane_y * screen_cord;
// 	raycasting->map_x = (int)game->player_x;
// 	raycasting->map_y = (int)game->player_y;
// 	raycasting->dist_between_x = fabs(1 / raycasting->ray_dir_x);
// 	raycasting->dist_between_y = fabs(1 / raycasting->ray_dir_y);
// }

// void	set_distance_to_next_x_or_y(t_raycasting *raycasting, t_game *game)
// {
// 	if (raycasting->ray_dir_x < 0)
// 	{
// 		raycasting->step_x = -1;
// 		raycasting->side_dest_x = (game->player_x - raycasting->map_x)
// 			* raycasting->dist_between_x;
// 	}
// 	else
// 	{
// 		raycasting->step_x = 1;
// 		raycasting->side_dest_x = (raycasting->map_x + 1.0 - game->player_x)
// 			* raycasting->dist_between_x;
// 	}
// 	if (raycasting->ray_dir_y < 0)
// 	{
// 		raycasting->step_y = -1;
// 		raycasting->side_dest_y = (game->player_y - raycasting->map_y)
// 			* raycasting->dist_between_y;
// 	}
// 	else
// 	{
// 		raycasting->step_y = 1;
// 		raycasting->side_dest_y = (raycasting->map_y + 1.0 - game->player_y)
// 			* raycasting->dist_between_y;
// 	}
// }

// void	find_wall_line_height_and_dist(t_raycasting *raycasting, t_game *game,
// 		int side)
// {
// 	if (side == 0)
// 		raycasting->wall_dist = (raycasting->map_x - game->player_x + (1
// 					- raycasting->step_x) / 2) / raycasting->ray_dir_x;
// 	else
// 		raycasting->wall_dist = (raycasting->map_y - game->player_y + (1
// 					- raycasting->step_y) / 2) / raycasting->ray_dir_y;
// 	raycasting->line_height = (int)(SCREEN_HEIGHT / raycasting->wall_dist);
// }

// int	find_wall_side_dist_and_height(t_raycasting *raycasting, t_game *game)
// {
// 	int	hit;
// 	int	side;

// 	hit = 0;
// 	while (hit == 0)
// 	{
// 		if (raycasting->side_dest_x < raycasting->side_dest_y)
// 		{
// 			raycasting->side_dest_x += raycasting->dist_between_x;
// 			raycasting->map_x += raycasting->step_x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			raycasting->side_dest_y += raycasting->dist_between_y;
// 			raycasting->map_y += raycasting->step_y;
// 			side = 1;
// 		}
// 		if (game->map[raycasting->map_x][raycasting->map_y] > '0')
// 			hit = 1;
// 	}
// 	return (side);
// }

// double	find_draw_pos_wall_width(t_raycasting *raycasting, t_game *game,
// 		int side)
// {
// 	double	wall_width;
// 	(void)side;

// 	// printf("%f \n", raycasting->wall_dist);
// 	raycasting->draw_start = (-raycasting->line_height + SCREEN_HEIGHT) / 2
// 		+ (int)(raycasting->wall_dist + raycasting->line_height / 5)
// 		* game->move_level / 2;
// 	if (raycasting->draw_start < 0)
// 		raycasting->draw_start = 0;
// 	raycasting->draw_end = (raycasting->line_height + SCREEN_HEIGHT) / 2
// 		+ (int)(raycasting->wall_dist + raycasting->line_height / 5)
// 		* game->move_level / 2;
// 	if (raycasting->draw_end >= SCREEN_HEIGHT)
// 		raycasting->draw_end = SCREEN_HEIGHT - 1;
// 	if (side == 0)
// 		wall_width = game->player_y + raycasting->wall_dist
// 			* raycasting->ray_dir_y;
// 	else
// 		wall_width = game->player_x + raycasting->wall_dist
// 			* raycasting->ray_dir_x;
// 	wall_width -= floor(wall_width);
// 	return (wall_width);
// }

// int	find_tex_index(t_raycasting *raycasting, int side)
// {
// 	int	tex_index;

// 	if (side == 0)
// 	{
// 		if (raycasting->ray_dir_x > 0)
// 			tex_index = 1;
// 		else
// 			tex_index = 0;
// 	}
// 	else
// 	{
// 		if (raycasting->ray_dir_y > 0)
// 			tex_index = 3;
// 		else
// 			tex_index = 2;
// 	}
// 	return (tex_index);
// }

// void	prepare_writing_to_img(t_game *game, t_raycasting *raycasting,
// 		int tex_x, int x)
// {
// 	int	y;
// 	int	tex_y;
// 	int	color;

// 	y = 0;
// 	while (y < SCREEN_HEIGHT)
// 	{
// 		if (y < raycasting->draw_start)
// 			set_pixel_color(game, x, y, game->sky_color);
// 		if (y >= raycasting->draw_start && y <= raycasting->draw_end)
// 		{
// 			tex_y = (((y * 2 - SCREEN_HEIGHT - (raycasting->wall_dist
// 								+ raycasting->line_height / 5)
// 							* game->move_level + raycasting->line_height) / 2)
// 					* raycasting->tex->height / raycasting->line_height);
// 			if (tex_y > raycasting->tex->height)
// 				tex_y = raycasting->tex->height;
// 			if (tex_y < 0)
// 				tex_y = 0;
// 			color = *(int *)(raycasting->tex->data + ((tex_y)
// 						* (raycasting->tex->size_line) + tex_x * 4));
// 			set_pixel_color(game, x, y, color);
// 		}
// 		if (y > raycasting->draw_end)
// 			set_pixel_color(game, x, y, game->ground_color);
// 		y++;
// 	}
// }

// void	cast_rays_and_generate_image(t_game *game, t_raycasting *raycasting)
// {
// 	int		tex_x;
// 	double	wall_width;
// 	int		x;
// 	int		side;

// 	x = 0;
// 	while (x < SCREEN_WIDTH)
// 	{
// 		set_initial_values(raycasting, game, x);
// 		set_distance_to_next_x_or_y(raycasting, game);
// 		side = find_wall_side_dist_and_height(raycasting, game);
// 			find_wall_line_height_and_dist(raycasting, game, side);
// 	// if(hit == 1 && raycasting->wall_dist < 1)
// 	// 	game->map[raycasting->map_x][raycasting->map_y] ='0';
// 		wall_width = find_draw_pos_wall_width(raycasting, game, side);
// 		raycasting->tex = &game->wall_tex[find_tex_index(raycasting, side)];
// 		tex_x = (int)(wall_width * (double)raycasting->tex->width);
// 		if (side == 0 && raycasting->ray_dir_x > 0)
// 			tex_x = game->wall_tex[0].width - tex_x - 1;
// 		if (side == 1 && raycasting->ray_dir_y < 0)
// 			tex_x = game->wall_tex[0].width - tex_x - 1;
// 		prepare_writing_to_img(game, raycasting, tex_x, x);
// 		x++;
// 	}
// 	// destroy_image_and_clean_exit(game);
// }

// int	main_loop(t_game *game)
// {
// 	t_raycasting	raycasting;
// 	double			x;
// 	double			y;
// 	double			cam_x;
// 	double			cam_y;
// 	double			i;
// 	double			j;
// 	int				*map_co;

// 	// int c;
// 	// void *bird;
// 	move_player(game);
// 	if (!game->esc)
// 		mlx_mouse_move(game->mlx_ptr, game->win_ptr, SCREEN_HEIGHT / 2,
// 			SCREEN_WIDTH / 2);
// 	cast_rays_and_generate_image(game, &raycasting);
// 	x = 0;
// 	y = SCREEN_HEIGHT - 192;
// 	map_co = map_count(game->map_structure);
// 	while (x < 192)
// 	{
// 		cam_x = 2 * (x) / 192.0 - 1;
// 		y = SCREEN_HEIGHT - 192;
// 		while (y < SCREEN_HEIGHT)
// 		{
// 			cam_y = 2 * (SCREEN_HEIGHT - y) / 192.0 - 1;
// 			cam_y = -1.0 * cam_y;
// 			i = game->player_x + 8 * cam_y;
// 			j = game->player_y + 8 * cam_x;
// 			if ((int)i < 0 || (int)j < 0 || ((int)i > (int)sizeof(map_co) - 1
// 					/ 4 && (int)j > map_co[(int)i]))
// 				set_pixel_color(game, x, y, 0xff000000);
// 			else if (game->map[(int)i][(int)j] == '1')
// 				set_pixel_color(game, x, y, 0xffffff);
// 			else if ((int)((i - game->player_x) * (i - game->player_x) * 15 + (j
// 						- game->player_y) * (j - game->player_y) * 15) == 1)
// 				set_pixel_color(game, x, y, 0x000);
// 			else
// 				set_pixel_color(game, x, y, 0x00ff00);
// 			y++;
// 		}
// 		x++;
// 	}
// 	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0,
// 		0);
// 	usleep(20000);
// 	return (0);
// }

// void	manage_player_dir(t_game *game, t_map *map)
// {
// 	game->dir_x = 0;
// 	game->dir_y = 0;
// 	game->plane_x = 0;
// 	game->plane_y = 0;
// 	if (map->player_dir == 'N')
// 	{
// 		game->dir_x = -1;
// 		game->plane_y = 0.66;
// 	}
// 	else if (map->player_dir == 'S')
// 	{
// 		game->dir_x = 1;
// 		game->plane_y = -0.66;
// 	}
// 	else if (map->player_dir == 'E')
// 	{
// 		game->dir_y = 1;
// 		game->plane_x = 0.66;
// 	}
// 	else if (map->player_dir == 'W')
// 	{
// 		game->dir_y = -1;
// 		game->plane_x = -0.66;
// 	}
// }

// int	main(void)
// {
// 	t_map	map;
// 	t_game	game;

// 	parse_cub_file(&map, "./map.cub");
// 	game.map_structure = &map;
// 	game.mlx_ptr = mlx_init();
// 	game.win_ptr = mlx_new_window(game.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
// 			"CUBE 3D");
// 	mlx_mouse_hide(game.mlx_ptr, game.win_ptr);
// 	game.img.img_ptr = mlx_new_image(game.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	game.img.data = mlx_get_data_addr(game.img.img_ptr, &game.img.bpp,
// 			&game.img.size_line, &game.img.endian);
// 	load_textures(&game, &map);
// 	game.esc = 0;
// 	game.map = map.map_2d;
// 	game.sky_color = map.sky_hexa;
// 	game.ground_color = map.ground_hexa;
// 	game.player_x = map.player_pos_x + 0.5;
// 	game.player_y = map.player_pos_y + 0.5;
// 	manage_player_dir(&game, &map);
// 	ft_memset(game.keys, 0, sizeof(game.keys));
// 	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, key_press, &game);
// 	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, key_release, &game);
// 	mlx_hook(game.win_ptr, 17, 0, destroy_image_and_clean_exit, &game);
// 	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
// 	mlx_loop(game.mlx_ptr);
// 	return (0);
// }

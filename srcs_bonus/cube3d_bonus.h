/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yand <mel-yand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:26:34 by ajamshid          #+#    #+#             */
/*   Updated: 2024/12/06 14:54:47 by mel-yand         ###   ########.fr       */
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

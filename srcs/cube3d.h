/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:26:34 by ajamshid          #+#    #+#             */
/*   Updated: 2024/11/28 13:52:12 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

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
	t_map		*map_structure;
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

	t_texture	wall_tex[4];
	t_image		img;
}				t_game;

int				parse_cub_file(t_map *map, char *map_cub);
char			*get_next_line(int fd);
int				parse_colors(t_map *map);
void			check_if_all_is_set(t_map *map);
void			check_if_map_is_surrounded(t_map *map);
int				destroy_image_and_clean_exit(t_game *game);
void			init_mlx_components(t_game *game);

void			clean_exit(t_map *map);
int				free_table(char **table);
char			*ft_strjoin_free(char const *s1, char const *s2);
int				ft_atoi_base(unsigned int decimal);
int				initialize_map(t_map *map, int fd);
void			init_player_dir(t_game *game, t_map *map);
void			set_initial_values(t_raycasting *raycasting, t_game *game,
					int x);
int				check_player_spawning_pos(t_map *map);
void			move_player(t_game *game);
void			load_textures(t_game *game, t_map *map);
void			cast_rays_and_generate_image(t_game *game,
					t_raycasting *raycasting);
int				find_tex_index(t_raycasting *raycasting, int side);
double			find_draw_pos_wall_width(t_raycasting *raycasting, t_game *game,
					int side);
void			set_pixel_color(t_game *game, int x, int y, int color);

void			set_distance_to_next_x_or_y(t_raycasting *raycasting,
					t_game *game);
void			find_wall_line_height_and_dist(t_raycasting *raycasting,
					t_game *game, int side);
int				find_wall_side_dist_and_height(t_raycasting *raycasting,
					t_game *game);
void			move_back_or_forward(t_game *game, double move_speed);
void			move_left_or_right(t_game *game, double move_speed);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:00:57 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/11/28 13:44:13 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

int	free_table(char **table)
{
	int	i;

	i = 0;
	while (table && table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	return (0);
}

void	clean_exit(t_map *map)
{
	(void)map;
	close(map->cub_fd);
	if (map)
	{
		if (map->north_wall)
			free_table(map->north_wall);
		if (map->south_wall)
			free_table(map->south_wall);
		if (map->east_wall)
			free_table(map->east_wall);
		if (map->west_wall)
			free_table(map->west_wall);
		if (map->sky_color)
			free_table(map->sky_color);
		if (map->ground_color)
			free_table(map->ground_color);
		if (map->map)
			free(map->map);
		if (map->map_2d)
			free_table(map->map_2d);
	}
	exit(0);
}

int	destroy_image_and_clean_exit(t_game *game)
{
	if (game->wall_tex[0].img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->wall_tex[0].img_ptr);
	if (game->wall_tex[1].img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->wall_tex[1].img_ptr);
	if (game->wall_tex[2].img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->wall_tex[2].img_ptr);
	if (game->wall_tex[3].img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->wall_tex[3].img_ptr);
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	if (game->mlx_ptr)
		free(game->mlx_ptr);
	free((void *)game->map_co);
	clean_exit(game->map_structure);
	return (0);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		len;
	char	*newstr;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	newstr = malloc(len);
	if (!newstr)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		newstr[i] = s1[i];
	j = 0;
	while (s2 && s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	if (s1)
		free((void *)s1);
	newstr[i + j] = '\0';
	return (newstr);
}

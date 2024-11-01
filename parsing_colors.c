/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:05:02 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/10/30 23:08:49 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	check_colors_range(char **sky, char **ground, t_map *map)
{
	if (!sky[0] || !sky[1] || !sky[2] || !ground[0] || !ground[1] || !ground[2])
	{
		ft_printf("Error\ncolors are not complete\n");
		free_table(sky);
		free_table(ground);
		clean_exit(map);
	}
	if (!((ft_atoi(sky[0]) < 256 && ft_atoi(sky[0]) > 0)
			|| (ft_atoi(sky[1]) < 256 && ft_atoi(sky[1]) > 0)
			|| (ft_atoi(sky[2]) < 256 && ft_atoi(sky[2]) > 0)
			|| (ft_atoi(ground[0]) < 256 && ft_atoi(ground[0]) > 0)
			|| (ft_atoi(ground[1]) < 256 && ft_atoi(ground[1]) > 0)
			|| (ft_atoi(ground[2]) < 256 && ft_atoi(ground[2]) > 0)))
	{
		ft_printf("Error\nnumber smaller than 255 ");
		ft_printf("or greater than 0 required in color");
		free_table(sky);
		free_table(ground);
		clean_exit(map);
	}
}

int	parse_colors(t_map *map)
{
	char	**sky;
	char	**ground;

	sky = ft_split(map->sky_color[0], ',');
	ground = ft_split(map->ground_color[0], ',');
	check_colors_range(sky, ground, map);
	map->sky_hexa = (ft_atoi(sky[0]) * 256 + ft_atoi(sky[1])) * 256
		+ ft_atoi(sky[2]);
	map->ground_hexa = (ft_atoi(ground[0]) * 256 + ft_atoi(ground[1])) * 256
		+ ft_atoi(ground[2]);
	free_table(sky);
	free_table(ground);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:29:28 by ajamshid          #+#    #+#             */
/*   Updated: 2024/11/26 19:41:54 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft.h"

int	set_map_line(t_map *map, char *line, int i)
{
	if (!ft_strncmp(&line[i], "1", 1) || !ft_strncmp(&line[i], "0", 1))
	{
		if (!map->map && map->map_last == 6 && (!ft_strncmp(&line[i], "1", 1)
				|| !ft_strncmp(&line[i], "0", 1)))
			map->map = ft_strdup(line);
		else if (map->map)
			map->map = ft_strjoin_free(map->map, line);
		if (!map->map)
			return (1);
	}
	else if (map->map && line[i] == '\n')
		return (1);
	else if (!map->map && line[i] == '\n')
		return (0);
	else
		return (1);
	return (0);
}

char	**seperate_info(t_map *map, char *line)
{
	int		i;
	char	**temp;

	i = 0;
	while (line[i] == ' ')
		i++;
	temp = ft_split(&line[i], '\n');
	if (!temp)
	{
		ft_printf("Error\nthere was a problem with allocation\n");
		clean_exit(map);
	}
	if (!temp[0][0] || temp[0][0] == '\0' || temp[0][0] == '\n')
	{
		ft_printf("info missing for an identifier please check .cub file\n");
		clean_exit(map);
	}
	map->map_last++;
	return (temp);
}

int	assign_to_map(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (!map->north_wall && !ft_strncmp(&line[i], "NO", 2))
		map->north_wall = seperate_info(map, &line[i + 3]);
	else if (!map->south_wall && !ft_strncmp(&line[i], "SO", 2))
		map->south_wall = seperate_info(map, &line[i + 3]);
	else if (!map->east_wall && !ft_strncmp(&line[i], "EA", 2))
		map->east_wall = seperate_info(map, &line[i + 3]);
	else if (!map->west_wall && !ft_strncmp(&line[i], "WE", 2))
		map->west_wall = seperate_info(map, &line[i + 3]);
	else if (!map->ground_color && !ft_strncmp(&line[i], "F", 1))
		map->ground_color = seperate_info(map, &line[i + 2]);
	else if (!map->sky_color && !ft_strncmp(&line[i], "C", 1))
		map->sky_color = seperate_info(map, &line[i + 2]);
	else if (set_map_line(map, line, i))
		return (1);
	return (0);
}

int	extract_from_cub_file(t_map *map, int fd)
{
	char	*map_line;
	int		i;
	int		j;

	j = 0;
	map_line = get_next_line(fd);
	while (map_line)
	{
		i = 0;
		while (map_line[i] == ' ' && j == 0)
			i++;
		if (j == 0 && map_line[i] != '\0' && assign_to_map(map, map_line))
		{
			ft_printf("Error\nthere is unknown identifier or more of ");
			ft_printf("the same in .cub or there is a newline in map\n");
			j = 1;
		}
		free(map_line);
		map_line = get_next_line(fd);
	}
	if (j)
		clean_exit(map);
	return (0);
}

int	parse_cub_file(t_map *map, char *map_cub)
{
	int	i;
	int	fd;

	i = 0;
	while (map_cub[i])
		i++;
	if (i < 5 || ft_strncmp(&map_cub[i - 4], ".cub", 4))
	{
		ft_printf("Error\nplease provide a valide .cub filename or path\n");
		exit(0);
	}
	fd = open(map_cub, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nthere was a problem opening the cub file\n");
		exit(0);
	}
	initialize_map(map, fd);
	extract_from_cub_file(map, fd);
	check_player_spawning_pos(map);
	check_if_all_is_set(map);
	parse_colors(map);
	return (0);
}

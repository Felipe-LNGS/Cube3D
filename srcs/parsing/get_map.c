/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 15:01:35 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

// Calcul la longueur et largeur de la map
int	get_height(char *filename, t_data *data)
{
	int		fd;
	char	*line;

	if (check_format(filename) == 1)
		exit_free(data, "Error\nNot the good format. Need .cub files");
	fd = open_file(data, filename);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		return (exit_free(data, "Error\nTry to read empty map."), 0);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		data->map->nb_lines++;
	}
	free(line);
	close(fd);
	return (0);
}

void	get_width(t_data *data)
{
	int	y;
	int	line_length;

	data->map->height = data->map->nb_lines - data->map->start_line;
	y = data->map->start_line;
	while (y < data->map->nb_lines)
	{
		line_length = 0;
		while (data->map->grid[y][line_length] != '\0'
			&& data->map->grid[y][line_length] != '\n')
		{
			line_length++;
		}
		if (line_length > data->map->width)
		{
			data->map->width = line_length;
		}
		y++;
	}
}

// Stock les valeurs lu avec gnl dans data->data->map
int	read_map(char *filename, t_data *data)
{
	int		fd;
	char	**line;
	int		i;

	i = 0;
	fd = open_file(data, filename);
	line = ft_calloc(sizeof(char *), data->map->nb_lines + 1);
	if (line == NULL)
		return (close(fd), exit_free(data, MERROR), 0);
	data->map->grid = ft_calloc(sizeof(char *), data->map->nb_lines + 1);
	if (data->map->grid == NULL)
		return (free(line), close(fd), exit_free(data, MERROR), 0);
	while (i < data->map->nb_lines)
	{
		line[i] = get_next_line(fd);
		if (line[i])
			data->map->grid[i] = ft_strdup(line[i]);
		if (data->map->grid[i] == NULL)
			return (free(line), close(fd), exit_free(data, MERROR), 0);
		free(line[i]);
		i++;
	}
	return (free(line), close(fd), 0);
}

static char	*allocate_map_line(t_data *data, int start)
{
	char	*line;
	int		x;

	line = ft_calloc(sizeof(char), data->map->width);
	if (!line)
		exit_free(data, MERROR);
	x = 0;
	while (data->map->grid[start][x] && data->map->grid[start][x] != '\n'
		&& x < data->map->width)
	{
		line[x] = data->map->grid[start][x];
		x++;
	}
	while (x < data->map->width)
	{
		line[x] = ' ';
		x++;
	}
	return (line);
}

void	rework_map(t_data *data)
{
	char	**map;
	int		y;
	int		start;

	y = 0;
	start = data->map->start_line;
	map = ft_calloc(sizeof(char *), data->map->height + 1);
	if (!map)
		exit_free(data, MERROR);
	while (start < data->map->nb_lines)
	{
		map[y] = allocate_map_line(data, start);
		y++;
		start++;
	}
	if (y < 1)
	{
		free(map);
		exit_free(data, "Error\nmissing map");
	}
	if (y < 3)
		(free_split(map), exit_free(data, "Error\nmap too small"));
	data->map->tmp_grid = map;
}

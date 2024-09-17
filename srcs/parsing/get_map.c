/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/17 10:46:01 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

// Calcul la longueur et largeur de la map
int	get_height(char *filename, t_data *data)
{
	int		fd;
	char	*line;

	fd = open_file(data, filename);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		return (exit_free(data, "Error\nTry to read empty map.\n"), 0);
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
	int	x;
	int	line_length;

	data->map->height = data->map->nb_lines - data->map->start_line;
	x = data->map->start_line;
	while (x < data->map->nb_lines)
	{
		line_length = 0;
		while (data->map->grid[x][line_length] != '\0'
			&& data->map->grid[x][line_length] != '\n')
		{
			line_length++;
		}
		if (line_length > data->map->width)
		{
			data->map->width = line_length;
		}
		x++;
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
	int		y;

	line = ft_calloc(sizeof(char), data->map->width);
	if (!line)
		exit_free(data, MERROR);
	y = 0;
	while (data->map->grid[start][y] && data->map->grid[start][y] != '\n'
		&& y < data->map->width)
	{
		line[y] = data->map->grid[start][y];
		y++;
	}
	while (y < data->map->width)
	{
		line[y] = ' ';
		y++;
	}
	return (line);
}

void	rework_map(t_data *data)
{
	char	**map;
	int		x;
	int		start;

	x = 0;
	start = data->map->start_line;
	map = ft_calloc(sizeof(char *), data->map->height + 1);
	if (!map)
		exit_free(data, MERROR);
	while (start < data->map->nb_lines)
	{
		map[x] = allocate_map_line(data, start);
		x++;
		start++;
	}
	data->map->tmp_grid = map;
}

// void	print_tmp_grid(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (data == NULL || data->map == NULL || data->map->tmp_grid == NULL)
// 	{
// 		printf("Error: No data to print.\n");
// 		return ;
// 	}
// 	while (i < data->map->height)
// 	{
// 		if (data->map->tmp_grid[i] != NULL)
// 		{
// 			printf("[%d][%s] \n", i, data->map->tmp_grid[i]);
// 		}
// 		else
// 		{
// 			printf("Line %d is NULL\n", i);
// 		}
// 		i++;
// 	}
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/11 10:40:12 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

// Verifie le format du fichier qui essaye d'etre ouvert
int	check_format(char *map)
{
	int	len;

	len = ft_strlen(map);
	if (len > 4 && (!ft_strcmp(map + len - 4, ".cub")) == 0)
	{
		ft_printf(RED "Error\nThis is not the good format.\n" RESET);
		exit(0);
	}
	return (1);
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, __O_DIRECTORY);
	if (fd > 0)
	{
		ft_printf(RED "Error\nU can't open .cub directory\n" RESET);
		exit(0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(RED "Error\nFailed to open file.\n" RESET);
		exit(0);
	}
	return (fd);
}

// Calcul la longueur et largeur de la map
int	get_height(char *filename, t_data *data)
{
	int		fd;
	char	*line;

	fd = open_file(filename);
	line = get_next_line(fd);
	if (line == NULL)
		return (ft_printf(RED "Error\nTry to read empty map.\n" RESET),
			close(fd), exit(0), 0);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		data->map->nb_lines++;
	}
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
	fd = open_file(filename);
	line = malloc(sizeof(char *) * data->map->nb_lines);
	if (line == NULL)
		return (close(fd), 0);
	data->map->grid = malloc(sizeof(char *) * data->map->nb_lines);
	if (data->map->grid == NULL)
		return (free(line), close(fd), 0);
	while (i < data->map->nb_lines)
	{
		line[i] = get_next_line(fd);
		if (line[i])
			data->map->grid[i] = ft_strdup(line[i]);
		if (data->map->grid[i] == NULL)
			return (free(line), close(fd), printf(RED "MALLOC ERROR\n"),
				exit(0), 0);
		free(line[i]);
		i++;
	}
	return (free(line), close(fd), 1);
}

void	rework_map(t_data *data)
{
	char	**tmp_grid;
	int		x;
	int		y;
	int		line_length;

	y = 0;
	x = data->map->start_line;
	tmp_grid = ft_calloc(sizeof(char *), (data->map->height + 1));
	if (!tmp_grid)
		return ;
	while (x < data->map->nb_lines)
	{
		tmp_grid[y] = malloc(sizeof(char) * (data->map->width + 1));
		if (!tmp_grid[y])
		{
			free_split(tmp_grid);
			return ;
		}
		line_length = 0;
		while (line_length < data->map->width
			&& data->map->grid[x][line_length] != '\0')
		{
			tmp_grid[y][line_length] = data->map->grid[x][line_length];
			line_length++;
		}
		tmp_grid[y][line_length] = '\0';
		x++;
		y++;
	}
	data->map->tmp_grid = tmp_grid;
}

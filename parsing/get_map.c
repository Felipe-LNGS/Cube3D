/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/11 15:41:05 by plangloi         ###   ########.fr       */
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

static int	open_file(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, __O_DIRECTORY);
	if (fd > 0)
	{
		 return (exit_free(data, "Error\nTry to read empty map."), 1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (exit_free(data, "Error\nFailed to open file."), 1);
	return (fd);
}

// Calcul la longueur et largeur de la map
int	get_height(char *filename, t_data *data)
{
	int		fd;
	char	*line;

	fd = open_file(data, filename);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), exit_free(data, "Error\nTry to read empty map.\n"), 0);
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
	fd = open_file(data ,filename);
	line = ft_calloc(sizeof(char *), data->map->nb_lines + 1);
	if (line == NULL)
		return ( close(fd), exit_free(data, MERROR),0);
	data->map->grid = ft_calloc(sizeof(char *), data->map->nb_lines + 1);
	if (data->map->grid == NULL)
		return ( free(line), close(fd),exit_free(data, MERROR), 0);
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

void rework_map(t_data *data)
{
    char **tmp_grid;
    int x;
    int line_length;
 
    x =  data->map->start_line; 
    tmp_grid = ft_calloc(sizeof(char *), (data->map->height));
    if (!tmp_grid)
       	exit_free(data, MERROR);
    while (x < data->map->nb_lines)
    {
        tmp_grid[x] = ft_calloc(sizeof(char), (data->map->width + 1));
        if (!tmp_grid[x])
			exit_free(data, MERROR);
        line_length = 0;
        while (data->map->grid[x][line_length] != '\n' && line_length < data->map->width)
        {
            tmp_grid[x][line_length] = data->map->grid[x][line_length];
            line_length++;
        }
        while (line_length < data->map->width)
        {
            tmp_grid[x][line_length] = ' ';
            line_length++;
        }
        // tmp_grid[x][line_length] = '\0';
		x++;
    }
    data->map->tmp_grid = tmp_grid;
}




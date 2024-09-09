/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:21:33 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/09 18:48:08 by plangloi         ###   ########.fr       */
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
int	get_dimensions(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		line_length;

	fd = open_file(filename);
	line = get_next_line(fd);
	if (line == NULL)
		return (ft_printf(RED "Error\nTry to read empty map.\n" RESET),
			close(fd), exit(0), 0);
	while (line)
	{
		line_length = 0;
		while (line[line_length] != '\0' && line[line_length] != '\n')
			line_length++;
		if (line_length > data->map->width)
			data->map->width = line_length;
		free(line);
		line = get_next_line(fd);
		data->map->nb_lines++;
	}
	close(fd);
	return (0);
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
		// if (data->map->grid[i] == NULL)
		// 	return (free(line), close(fd), 0);
		free(line[i]);
		i++;
	}
	return (free(line), close(fd), 1);
}
void	free_grid(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map->nb_lines)
	{
		free(data->map->grid[i]);
		i++;
	}
	free(data->map->grid);
}

void	print_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->nb_lines)
	{
		j = 0;
		while (data->map->tmp_grid[i][j])
		{
			ft_printf("%c", data->map->tmp_grid[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
	// printf("big len %d\n", data->map->width);
}

char	**rework_map(t_data *data)
{
	char	**tmp_grid;
	int		x;
	int		y;
	int		line_length;

	x = 0;
	tmp_grid = data->map->grid;
	while (x < data->map->nb_lines)
	{
		y = 0;
		line_length = 0;
		while (tmp_grid[x][line_length] != '\0'
			&& tmp_grid[x][line_length] != '\n')
			line_length++;
		while (y < line_length + 1)
		{

			if (tmp_grid[x][y] == '\n' && tmp_grid[x][y + 1] == '\0' && line_length > 0)
			{					
				while (line_length < data->map->width)
				{
					tmp_grid[x][y + 1] = '*';
					y++;
					line_length++;
				}
				tmp_grid[x][y] = '\0';
			}
			y++;
		}
		x++;
	}
	return (tmp_grid);
}

// verifier autour de chaque 0 si il y a autre chose que un 1 c'est carton rouge
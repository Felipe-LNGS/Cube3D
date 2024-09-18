/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:38:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 12:21:37 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	check_valid_char(t_data *data)
{
	int	x;
	int	y;
	int	nb_start;

	nb_start = 0;
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if ((ft_strchr(" 01NSEW\n", data->map->tmp_grid[y][x]) == NULL))
				exit_free(data, "Invalid character need to put only 01NSEW");
			if ((ft_strchr("NSEW", data->map->tmp_grid[y][x]) != NULL))
			{
				data->pos[X] = (double)y + 0.5;
				data->pos[Y] = (double)x + 0.5;
				nb_start++;
			}
			x++;
		}
		y++;
	}
	if (nb_start > 1 || nb_start == 0)
		exit_free(data, "Error: more than one or no start position found.");
}

void	check_is_close(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	map = data->map->tmp_grid;
	y = -1;
	while (++y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (ft_strchr("0NSEW", map[y][x]))
			{
				if (y == 0 || y == data->map->height - 1 || x == 0
					|| x == data->map->width - 1)
					exit_free(data, "Map not closed: character on the edge.");
				if ((y + 1 < data->map->nb_lines && map[y + 1][x] == ' ') || (y
						- 1 >= 0 && map[y - 1][X] == ' ') || (x
						+ 1 < data->map->width && map[y][x + 1] == ' ') || (x
						- 1 >= 0 && map[y][x - 1] == ' '))
					exit_free(data, "Map not closed: adjacent to empty space");
			}
			x++;
		}
	}
}

void	find_start_line(t_data *data)
{
	int	i;

	i = 0;
	while (data->map->grid[i])
	{
		if (is_info(data->map->grid[i]))
			stock_info(data->map->grid[i], data);
		else if (ft_strchr(data->map->grid[i], '0')
			|| ft_strchr(data->map->grid[i], '1'))
		{
			data->map->start_line = i;
			return ;
		}
		i++;
	}
	data->map->start_line = data->map->nb_lines;
}

void	parse_map(t_data *data, char *filename)
{
	char	**tab;

	tab = NULL;
	get_height(filename, data);
	read_map(filename, data);
	find_start_line(data);
	get_width(data);
	rework_map(data);
	check_valid_char(data);
	check_is_close(data);
	get_pos(data);
	split_rgb(data, data->map->f, 'F', tab);
	split_rgb(data, data->map->c, 'C', tab);
}

// printf("f path[%d]\n", data->map->f_color);
// printf("c path[%d]\n", data->map->c_color);
// print_map(data);
// printf("north[%s]\n", data->map->north_path);
// printf("s [%s]\n", data->map->south_path);
// printf("e [%s]\n", data->map->east_path);
// printf("w [%s]\n", data->map->west_path);
// printf("f [%s]\n", data->map->f);
// printf("c [%s]\n", data->map->c);
// printf("f path[%s]\n", data->map->f);
// printf("c path[%s]\n", data->map->c);
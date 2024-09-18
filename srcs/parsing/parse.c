/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:38:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 11:24:49 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	check_valid_char(t_data *data)
{
	int	x;
	int	y;
	int	nb_start;

	nb_start = 0;
	x = 0;
	while (x < data->map->height)
	{
		y = 0;
		while (y < data->map->width)
		{
			if ((ft_strchr(" 01NSEW\n", data->map->tmp_grid[x][y]) == NULL))
				exit_free(data, "Invalid character need to put only 01NSEW");
			if ((ft_strchr("NSEW", data->map->tmp_grid[x][y]) != NULL))
			{
				data->pos[X] = (double)x + 0.5;
				data->pos[Y] = (double)y + 0.5;
				nb_start++;
			}
			y++;
		}
		x++;
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
	x = -1;
	while (++x < data->map->height)
	{
		y = 0;
		while (y < data->map->width)
		{
			if (ft_strchr("0NSEW", map[x][y]))
			{
				if (x == 0 || x == data->map->height - 1 || y == 0
					|| y == data->map->width - 1)
					exit_free(data, "Map not closed: character on the edge.");
				if ((x + 1 < data->map->nb_lines && map[x + 1][y] == ' ') || (x
						- 1 >= 0 && map[x - 1][y] == ' ') || (y
						+ 1 < data->map->width && map[x][y + 1] == ' ') || (y
						- 1 >= 0 && map[x][y - 1] == ' '))
					exit_free(data, "Map not closed: adjacent to empty space");
			}
			y++;
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
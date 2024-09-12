/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:38:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/12 16:44:18 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
			if ((ft_strchr(" 01NSEW", data->map->tmp_grid[x][y]) == NULL))
				exit_free(data, "Invalid character need to put only 01NSEW");
			if ((ft_strchr("NSEW", data->map->tmp_grid[x][y]) != NULL))
			{
				data->posx_p = x;
				data->posy_p = y;
				nb_start++;
			}
			y++;
		}
		if (nb_start > 1)
			exit_free(data, "Error: more than one start position found.");
		x++;
	}
}

void	check_is_close(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	map = data->map->tmp_grid;
	x = 0;
	while (x < data->map->height)
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
					exit_free(data, "Map not closed: adjacent to empty space.");
			}
			y++;
		}
		x++;
	}
}
void	set_dir(t_data *data, char who)
{
	if (who == 'N')
	{
		data->map_x = 0;
		data->map_y = 1;
	}
	if (who == 'S')
	{
		data->map_x = 0;
		data->map_y = -1;
	}
	if (who == 'E')
	{
		data->map_x = 1;
		data->map_y = 0;
	}
	if (who == 'W')
	{
		data->map_x = -1;
		data->map_y = 0;
	}
}
void	get_pos(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	map = data->map->tmp_grid;
	x = 0;
	while (x < data->map->height)
	{
		y = 0;
		while (y < data->map->width)
		{
			if (ft_strchr("N", map[x][y]))
				set_dir(data, 'N');
			if (ft_strchr("E", map[x][y]))
				set_dir(data, 'E');
			if (ft_strchr("S", map[x][y]))
				set_dir(data, 'S');
			if (ft_strchr("W", map[x][y]))
				set_dir(data, 'W');
			y++;
		}
		x++;
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

void	parse_map(t_data *data)
{
	find_start_line(data);
	get_width(data);
	rework_map(data);
	print_map(data);
	check_valid_char(data);
	check_is_close(data);
	get_pos(data);
	printf("f path[%s]\n", data->map->f);
	printf("c path[%s]\n", data->map->c);
	split_rgb(data, data->map->f, 'F');
	split_rgb(data, data->map->c, 'C');
	printf("f color[%d]\n", data->map->f_color);
	printf("c color[%d]\n", data->map->c_color);
	printf("north[%s]\n", data->map->north_path);
	printf("s [%s]\n", data->map->south_path);
	printf("e [%s]\n", data->map->east_path);
	printf("w [%s]\n", data->map->west_path);
	printf("f [%s]\n", data->map->f);
	printf("c [%s]\n", data->map->c);
	printf("pos x %d\n", data->posx_p);
	printf("pos y %d\n", data->posy_p);
	printf("pos map x %d\n", data->map_x);
	printf("pos map y %d\n", data->map_y);
}

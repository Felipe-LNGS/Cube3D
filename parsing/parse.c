/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:38:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/12 12:23:20 by plangloi         ###   ########.fr       */
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
		while (y < data->map->width )
		{
			if ((ft_strchr(" 01NSEW\n", data->map->tmp_grid[x][y]) == NULL))
			{
				ft_printf("[%d][%d][%c]\n", x, y, data->map->tmp_grid[x][y]);
				exit_free(data, "Invalid character need to put only 01NSEW");
			}
			if ((ft_strchr("NSEW", data->map->tmp_grid[x][y]) != NULL))
				nb_start++;
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
				if (x == 0 || x == data->map->nb_lines - 1 || y == 0
					|| y == data->map->width - 1)
				{
					ft_printf(RED "Map not closed: character on the edge\n" RESET);
					exit(1);
				}
				if ((x + 1 < data->map->nb_lines && map[x + 1][y] == ' ') || (x
						- 1 >= 0 && map[x - 1][y] == ' ') || (y
						+ 1 < data->map->width && map[x][y + 1] == ' ') || (y
						- 1 >= 0 && map[x][y - 1] == ' '))
				{
					ft_printf(RED "Map not closed: adjacent to empty space\n" RESET);
				}
			}
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
	printf("north[%s]\n", data->map->north_path);
	printf("s [%s]\n", data->map->south_path);
	printf("e [%s]\n", data->map->east_path);
	printf("w [%s]\n", data->map->west_path);
	printf("f [%s]\n", data->map->f);
	printf("c [%s]\n", data->map->c);
	check_valid_char(data);
	check_is_close(data);
	split_rgb(data, data->map->f, 'F');
	split_rgb(data, data->map->c, 'C');
	
}

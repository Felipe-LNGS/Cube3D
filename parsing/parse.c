/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:38:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/10 17:45:35 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	check_valid_char(t_data *data)
{
	int		x;
	int		y;
	char	*valid_char;
	int		nb_start;
	char	*start;

	nb_start = 0;
	valid_char = "01NSEW ";
	start = "NSEW";
	x = data->map->start_line;
	while (x < data->map->height)
	{
		y = -1;
		while (y++ < data->map->width)
		{
			if ((ft_strchr(valid_char, data->map->tmp_grid[x][y]) == 0))
			{
				ft_printf(RED "Invalid character '%c' need to put only \
				%s\n" RESET,
							data->map->tmp_grid[x][y],
							valid_char);
				exit(1);
				// free_exit + message
			}
			if ((ft_strchr(start, data->map->tmp_grid[x][y]) == 0))
				start++;
		}
		if (nb_start > 1)
		{
			ft_printf(RED "Error: more than one start position found\n" RESET);
			exit(1);
			// free_exit + message
		}
		x++;
	}
}

void	check_is_close(t_data *data)
{
	int		x;
	int		y;
	char	*valid_path;

	valid_path = "NSEW ";
	x = data->map->start_line;
	while (x < data->map->height)
	{
		y = -1;
		while (y++ < data->map->width)
		{
			if ((ft_strchr(valid_path, data->map->tmp_grid[x][y]) == 0))
			{
				if (y == 0 || x == 0 || x == data->map->height || y
					+ 1 == data->map->width)
				{
					ft_printf(RED "Invalid character  need to put only\n" RESET);
					exit(1);
					// free_exit + message
				}
				else if (data->map->tmp_grid[x + 1][y] == ' '
					|| data->map->tmp_grid[x - 1][y] == ' '
					|| data->map->tmp_grid[x][y + 1] == ' '
					|| data->map->tmp_grid[x][y - 1] == ' ')
				{
					ft_printf(RED "Invalid character  need to put only\n" RESET);
					exit(1);
					// free_exit + message
				}
			}
		}
		x++;
	}
}

void	parse_map(t_data *data)
{
	int i;

	i = 0;
	while (data->map->grid[i])
	{
		if (data->map->grid[i][0] == '\n' && data->map->grid[i][1] == '\0')
			data->map->start_line++;
		if (is_info(data->map->grid[i]) == 1)
			stock_info(data->map->grid[i], data);
		i++;
	}
	
	data->map->height = data->map->nb_lines - data->map->start_line;
printf("max lines%d\n", data->map->nb_lines);
	printf("max height %d\n", data->map->height);
	rework_map(data);
	print_map(data);

	// check_is_close(data);
	// check_valid_char(data);
}
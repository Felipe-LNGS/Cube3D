/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:38:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/10 16:17:06 by plangloi         ###   ########.fr       */
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
			if ((ft_strchr(valid_char, data->map->grid[x][y]) == 0))
			{
				ft_printf(RED "Invalid character '%c' need to put only %s\n" RESET, data->map->grid[x][y], valid_char);
				exit(1);
				//free_exit + message
			}
			if ((ft_strchr(start, data->map->grid[x][y]) == 0))
				start++;
		}
		if (start > 1)
			{
				ft_printf(RED "Error: more than one start position found\n" RESET);
				exit(1);
				//free_exit + message
			}
		x++;
	}
}

void	check_is_close(t_data *data)
{
	int	x;
	int	y;

	x = data->map->start_line;
	while (x < data->map->height)
	{
		y = -1;
		while (y++ < data->map->width)
		{
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
	}
	data->map->height = data->map->start_line - data->map->nb_lines;
	rework_map(data);
	check_is_close(data);
}
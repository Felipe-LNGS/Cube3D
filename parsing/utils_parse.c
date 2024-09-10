/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:21:33 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/10 15:38:18 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
		while (j < data->map->width)
		{
			ft_printf("%c", data->map->tmp_grid[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
}

char	*skip_space(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

int	check_is_close(t_data *data)
{
	int		x;
	int		y;
	char	*valid_char;
	int		nb_start;

	nb_start = 0;
	valid_char = "01NSEW";
	x = data->map->start_line;
	while (x < data->map->nb_lines - data->map->start_line)
	{
		y = 0;
		while (y < data->map->width)
		{
			if ((ft_strchr(valid_char, data->map->grid[x][y]) == 0))
				return (-1);
			y++;
		}
		x++;
	}
	return (1);
}

void	parse_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map->grid[i])
	{
		if (data->map->grid[i][0] == '\n' && data->map->grid[i][1] == '\0')
				data->map->start_line++;
		if (is_info(data->map->grid[i]) == 1)
			stock_info(data->map->grid[i], data);
	}
	rework_map(data);
	check_is_close(data);
	
}

// verifier autour de chaque 0 si il y a autre chose que un 1 c'est carton rouge
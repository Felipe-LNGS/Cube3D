/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:47:46 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 12:25:16 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void	set_dirplane(t_data *data, char who)
{
	if (who == 'N')
	{
		data->dir[X] = 0;
		data->dir[Y] = 1;
	}
	if (who == 'S')
	{
		data->dir[X] = 0;
		data->dir[Y] = -1;
	}
	if (who == 'E')
	{
		data->dir[X] = -1;
		data->dir[Y] = 0;
	}
	if (who == 'W')
	{
		data->dir[X] = 1;
		data->dir[Y] = 0;
	}
	data->plane[X] = data->dir[Y] * (-1) * 0.66;
	data->plane[Y] = data->dir[X] * 0.66;
}

void	get_pos(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	map = data->map->tmp_grid;
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				set_dirplane(data, map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

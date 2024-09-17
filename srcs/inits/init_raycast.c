
#include "../../include/cube.h"

static void	set_dirplane(t_data *data, char who)
{
	if (who == 'N')
	{
		data->dir[X] = 0;
		data->dir[Y] = -1;
	}
	if (who == 'S')
	{
		data->dir[X] = 0;
		data->dir[Y] = 1;
	}
	if (who == 'E')
	{
		data->dir[X] = 1;
		data->dir[Y] = 0;
	}
	if (who == 'W')
	{
		data->dir[X] = -1;
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
	x = 0;
	while (x < data->map->height)
	{
		y = 0;
		while (y < data->map->width)
		{
			if (ft_strchr("NSEW", map[x][y]))
			{
				set_dirplane(data, map[x][y]);
				return ;
			}
			y++;
		}
		x++;
	}
}

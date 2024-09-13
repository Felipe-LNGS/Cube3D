
#include "../../include/cube.h"

static void	set_plane(t_data *data)
{

    data->plane_x = data->dir_y * (-1) * 0.66;
    data->plane_y = data->dir_x * 0.66;
	// if (who == 'N')
	// {
	// 	data->plane_x = 0.66;
	// 	data->plane_y = 0;
	// }
	// if (who == 'S')
	// {
	// 	data->plane_x = -0.66;
	// 	data->plane_y = 0;
	// }
	// if (who == 'E')
	// {
	// 	data->plane_x = 0;
	// 	data->plane_y = 0.66;
	// }
	// if (who == 'W')
	// {
	// 	data->plane_x = 0;
	// 	data->plane_y = -0.66;
	// }
}
static void	set_dir(t_data *data, char who)
{
	if (who == 'N')
	{
		data->dir_x = 0;
		data->dir_y = 1;
	}
	if (who == 'S')
	{
		data->dir_x = 0;
		data->dir_y = -1;
	}
	if (who == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
	}
	if (who == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
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
			if (ft_strchr("NSEW", map[x][y]))
			{
				set_dir(data, map[x][y]);
				set_plane(data);
			}
			y++;
		}
		x++;
	}
}

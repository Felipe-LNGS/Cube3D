
#include "../../include/cube.h"

static void	set_plane(t_data *data, char who)
{
	// data->plane[X] = data->dir[Y] * (-1) * 0.66;
	// data->plane[Y] = data->dir[X] * 0.66;
	if (who == 'N')
	{
		data->plane[X] = 0.66;
		data->plane[Y] = 0;
	}
	if (who == 'S')
	{
		data->plane[X] = -0.66;
		data->plane[Y] = 0;
	}
	if (who == 'E')
	{
		data->plane[X] = 0;
		data->plane[Y] = 0.66;
	}
	if (who == 'W')
	{
		data->plane[X] = 0;
		data->plane[Y] = -0.66;
	}
}
static void	set_dir(t_data *data, char who)
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
				set_plane(data, map[x][y]);
				printf("Direction %c \n",map[x][y] );
				printf("dir[X]: %f, dir[Y]: %f\n", data->dir[X], data->dir[Y]);
				printf("plane[X]: %f, plane[Y]: %f\n", data->plane[X],
					data->plane[Y]);
				return ;
			}
			y++;
		}
		x++;
	}
}

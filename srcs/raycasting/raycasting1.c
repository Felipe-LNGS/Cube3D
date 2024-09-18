/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:28:35 by louismdv          #+#    #+#             */
/*   Updated: 2024/09/18 10:38:19 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	reset_buffer(int **buffer)
{
	int	j;

	j = -1;
	while (++j < SCREEN_H)
		free(buffer[j]);
	free(buffer);
}

void	ft_img_addr(t_data *data, int **buffer, t_imgs *img)
{
	int		i;
	int		j;
	int		index;

	ft_bzero(img, sizeof(t_imgs));
	img->mlx_img = mlx_new_image(data->mlx_ptr, SCREEN_W, SCREEN_H);
	img->addr_ptr = (int *)mlx_get_data_addr(img->mlx_img, &img->pixel_bits,
			&img->line_len, &img->endian);
	i = -1;
	while (++i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
		{
			index = i * (img->line_len / 4) + j;
			if (buffer[i][j] > 0)
				img->addr_ptr[index] = buffer[i][j];
			else if (i < SCREEN_H / 2)
				img->addr_ptr[index] = data->map->c_color;
			else
				img->addr_ptr[index] = data->map->f_color;
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->mlx_img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, img->mlx_img);
}

// initiate buffer to store final window image
int	**init_buffer(t_data *data)
{
	int	**buffer;
	int	bufindex;
	int	x;

	x = 0;
	bufindex = 0;
	buffer = ft_calloc(SCREEN_H + 1, sizeof(int *));
	if (!buffer)
		exit_free(data, "Error\nBuffer calloc\n");
	while (bufindex < SCREEN_H)
	{
		buffer[bufindex] = ft_calloc(SCREEN_W + 1, sizeof(int));
		if (!buffer[bufindex])
		{
			while (x < bufindex)
			{
				free(buffer[bufindex]);
				x++;
			}
			free(buffer);
			exit_free(data, MERROR);
		}
		bufindex++;
	}
	return (buffer);
}

// init ray_dir vector + camerax point
// init coordinates of box of the map we're in
// calculating ddist : length of ray from one x or y-side to next x or y-side
void	init_raycast(t_data *data, int x)
{
	data->camerax = 2.0 * x / (double)SCREEN_W - 1;
	data->ray_dir[X] = data->dir[X] + data->plane[X] * data->camerax;
	data->ray_dir[Y] = data->dir[Y] + data->plane[Y] * data->camerax;
	data->map_p[X] = (int)data->pos[X];
	data->map_p[Y] = (int)data->pos[Y];
	data->ddist[X] = fabs(1 / data->ray_dir[X]);
	data->ddist[Y] = fabs(1 / data->ray_dir[Y]);
}

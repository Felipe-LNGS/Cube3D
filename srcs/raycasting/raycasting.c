/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:19:15 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 12:24:58 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void	reset_buffer(int **buffer)
{
	int	j;

	j = -1;
	while (++j < SCREEN_H)
		free(buffer[j]);
	free(buffer);
}

static void	ft_img_addr(t_data *data, int **buffer)
{
	int		i;
	int		j;
	int		index;
	t_imgs	img;
	ft_bzero(&img, sizeof(t_imgs));
	img.mlx_img = mlx_new_image(data->mlx_ptr, SCREEN_W, SCREEN_H);
	img.addr_ptr = (int *)mlx_get_data_addr(img.mlx_img, &img.pixel_bits,
			&img.line_len, &img.endian);
	i = -1;
	while (++i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
		{
			index = i * (img.line_len / 4) + j;
			if (buffer[i][j] > 0)
				img.addr_ptr[index] = buffer[i][j];
			else if (i < SCREEN_H / 2)
				img.addr_ptr[index] = data->map->c_color;
			else
				img.addr_ptr[index] = data->map->f_color;
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, img.mlx_img);
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

// calculate step and initial sideDist
void	step_sidedist(t_data *data)
{
	if (data->ray_dir[X] < 0)
	{
		data->step[X] = -1;
		data->side_dist[X] = ((data->pos[X] - data->map_p[X]) * data->ddist[X]);
	}
	else if (data->ray_dir[X] > 0)
	{
		data->step[X] = 1;
		data->side_dist[X] = (data->map_p[X] + 1.0 - data->pos[X])
			* data->ddist[X];
	}
	if (data->ray_dir[Y] < 0)
	{
		data->step[Y] = -1;
		data->side_dist[Y] = (data->pos[Y] - data->map_p[Y]) * data->ddist[Y];
	}
	else if (data->ray_dir[Y] > 0)
	{
		data->step[Y] = 1;
		data->side_dist[Y] = (data->map_p[Y] + 1.0 - data->pos[Y])
			* data->ddist[Y];
	}
}

// casts rays in raydir direction until it hits a '1' on the map
// jump to next map square, either in x-direction, or in y-direction
// Check if ray has hit a wall
void	dda(t_data *data)
{
	data->hit = 0;
	while (data->hit == 0)
	{
		if (data->side_dist[X] < data->side_dist[Y])
		{
			data->side_dist[X] += data->ddist[X];
			data->map_p[X] += data->step[X];
			data->side = X;
		}
		else
		{
			data->side_dist[Y] += data->ddist[Y];
			data->map_p[Y] += data->step[Y];
			data->side = Y;
		}
		printf("data->map->width %d\n", data->map->width);
		printf("data->map->height %d\n", data->map->height);
		
		if (data->map_p[X] < 0 || data->map_p[Y] < 0
			|| data->map_p[X] >= data->map->width
			|| data->map_p[Y] >= data->map->height)
			break ;
		if (data->map->tmp_grid[data->map_p[X]][data->map_p[Y]] == '1')
			data->hit = 1;
	}
}

void	projection_prep(t_data *data)
{
	if (data->side == X)
		data->perpwalldist = (data->side_dist[X] - data->ddist[X]);
	else
		data->perpwalldist = (data->side_dist[Y] - data->ddist[Y]);
	data->line_h = (int)(SCREEN_H / data->perpwalldist);
	data->draw_start = SCREEN_H / 2 - (data->line_h / 2);
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_h / 2 + SCREEN_H / 2;
	if (data->draw_end >= SCREEN_H)
		data->draw_end = SCREEN_H - 1;
	if (data->side == X)
	{
		if (data->ray_dir[X] < 0)
			data->texnum = WE;
		else
			data->texnum = EA;
	}
	else
	{
		if (data->ray_dir[Y] > 0)
			data->texnum = SO;
		else
			data->texnum = NO;
	}
}

void	fill_buffer(t_data *data, int **buffer, int x)
{
	if (data->side == X)
		data->wallx = data->pos[Y] + data->perpwalldist * data->ray_dir[Y];
	else
		data->wallx = data->pos[X] + data->perpwalldist * data->ray_dir[X];
	data->wallx -= floor((data->wallx));
	data->tex[X] = (int)(data->wallx * (double)SIZE_IMG);
	if ((data->side == X && data->ray_dir[X] > 0) || (data->side == Y
			&& data->ray_dir[Y] < 0))
		data->tex[X] = SIZE_IMG - data->tex[X] - 1;
	data->texstep = 1.0 * SIZE_IMG / data->line_h;
	data->texpos = (data->draw_start - SCREEN_H / 2.0 + data->line_h / 2.0)
		* data->texstep;
	data->y = data->draw_start;
	while (data->y < data->draw_end)
	{
		data->tex[Y] = (int)data->texpos & (SIZE_IMG - 1);
		data->texpos += data->texstep;
		data->color = data->img->texture[data->texnum][SIZE_IMG * data->tex[Y]
			+ data->tex[X]];
		buffer[data->y][x] = data->color;
		data->y++;
	}
}

void	raycast(t_data *data)
{
	int	x;
	int	**buffer;

	buffer = init_buffer(data);
	x = 0;
	while (x < SCREEN_W)
	{
		init_raycast(data, x);
		step_sidedist(data);
		dda(data);
		projection_prep(data);
		fill_buffer(data, buffer, x);
		x++;
	}
	ft_img_addr(data, buffer);
	reset_buffer(buffer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:19:15 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 10:39:37 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

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
	int		x;
	int		**buffer;
	t_imgs	img;

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
	ft_img_addr(data, buffer, &img);
	reset_buffer(buffer);
}

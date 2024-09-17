/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/17 12:10:40 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cube.h"

int	can_move(t_data *data, double x, double y)
{
	if (x < 0.25 || x >= data->map->width - 1.25)
		return (0);
	if (data->pos[Y] < 0.25 || data->pos[Y] >= data->map->height - 0.25)
		return (0);
	if (data->pos[X] < 0.25 || data->pos[X] >= data->map->width - 1.25)
		return (0);
	if (y < 0.25 || y >= data->map->height - 0.25)
		return (0);
	if (data->map->tmp_grid[(int)(x)][(int)(y)] == '1')
		return (0);
	return (1);
}

int	y_move(t_data *data, char upordown)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (upordown == 'U')
	{
		x_tmp = data->pos[X] + data->dir[X] * (P_SPEED);
		y_tmp = data->pos[Y] + data->dir[Y] * (P_SPEED);
	}
	else if (upordown == 'D')
	{
		x_tmp = data->pos[X] - data->dir[X] * (P_SPEED);
		y_tmp = data->pos[Y] - data->dir[Y] * (P_SPEED);
	}
	if (!can_move(data, x_tmp, y_tmp))
		return (0);
	else
	{
		data->pos[X] = x_tmp;
		data->pos[Y] = y_tmp;
	}
	return (1);
}

int	x_move(t_data *data, char leftorright)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (leftorright == 'L')
	{
		x_tmp = data->pos[X] + data->dir[Y] * P_SPEED;
		y_tmp = data->pos[Y] - data->dir[X] * P_SPEED;
	}
	else if (leftorright == 'R')
	{
		x_tmp = data->pos[X] - data->dir[Y] * P_SPEED;
		y_tmp = data->pos[Y] + data->dir[X] * P_SPEED;
	}
	// printf("Position: x[%f] y[%f]\n\n", data->pos[X], data->pos[Y]);
	// printf("Direction: dir[X]: %f, dir[Y]: %f\n\n", data->dir[X], data->dir[Y]);
	// printf("Plane: plane[X]: %f, plane[Y]: %f\n", data->plane[X],
	// 	data->plane[Y]);
	if (!can_move(data, x_tmp, y_tmp))
		return (0);
	else
	{
		data->pos[X] = x_tmp;
		data->pos[Y] = y_tmp;
	}
	return (1);
}

int	moving(t_data *data)
{
	int move;

	move = 0;
	printf("move [%d][%d]\n", data->move[X],  data->move[Y]);
	if (data->move[Y] == 1)
		move += y_move(data, 'U');
	if (data->move[Y] == -1)
		move += y_move(data, 'D');
	if (data->move[X] == -1)
		move += x_move(data, 'L');
	if (data->move[X] == 1)
		move += x_move(data, 'R');
	if (data->rotate > 0)
		move += l_rotate(data);
	if (data->rotate < 0)
		move += r_rotate(data);
	return (move);
}
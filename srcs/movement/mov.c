/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:00:48 by lmerveil          #+#    #+#             */
/*   Updated: 2024/09/17 12:02:39 by louismdv         ###   ########.fr       */
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

int	y_move(t_data *data, int upordown)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (upordown == 0)
	{
		x_tmp = data->pos[X] + data->dir[X] * (P_SPEED * 1.7);
		y_tmp = data->pos[Y] + data->dir[Y] * (P_SPEED * 1.7);
	}
	else if (upordown == 1)
	{
		x_tmp = data->pos[X] - data->dir[X] * (P_SPEED * 1.7);
		y_tmp = data->pos[Y] - data->dir[Y] * (P_SPEED * 1.7);
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

int	x_move(t_data *data, int leftorright)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (leftorright == 0)
	{
		x_tmp = data->pos[X] - data->dir[Y] * P_SPEED;
		y_tmp = data->pos[Y] + data->dir[X] * P_SPEED;
	}
	else if (leftorright == 1)
	{
		x_tmp = data->pos[X] + data->dir[Y] * P_SPEED;
		y_tmp = data->pos[Y] - data->dir[X] * P_SPEED;
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

int	moving(t_data *data)
{
	int	move;

	move = 0;
	if (data->move[Y] == 1)
		move += y_move( data, 0);
	if (data->move[Y] == -1)
		move += y_move( data, 1);
	if (data->move[X] == -1)
		move += x_move( data, 0);
	if (data->move[X] == 1)
		move += x_move( data, 1);
	if (data->rotate < 0)
		move += l_rotate(data);
	if (data->rotate > 0)
		move += r_rotate(data);
	return (move);
}
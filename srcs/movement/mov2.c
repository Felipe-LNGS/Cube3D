/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:58:15 by jfita             #+#    #+#             */
/*   Updated: 2024/09/18 09:48:06 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

int	l_rotate(t_data *data)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->dir[X];
	old_planex = data->plane[X];
	data->dir[X] = data->dir[X] * cos(R_SPEED) - data->dir[Y] * sin(R_SPEED);
	data->dir[Y] = old_dirx * sin(R_SPEED) + data->dir[Y] * cos(R_SPEED);
	data->plane[X] = data->plane[X] * cos(R_SPEED) - data->plane[Y]
		* sin(R_SPEED);
	data->plane[Y] = old_planex * sin(R_SPEED) + data->plane[Y] * cos(R_SPEED);
	return (1);
}

int	r_rotate(t_data *data)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->dir[X];
	old_planex = data->plane[X];
	data->dir[X] = data->dir[X] * cos(-R_SPEED) - data->dir[Y] * sin(-R_SPEED);
	data->dir[Y] = old_dirx * sin(-R_SPEED) + data->dir[Y] * cos(-R_SPEED);
	data->plane[X] = data->plane[X] * cos(-R_SPEED) - data->plane[Y]
		* sin(-R_SPEED);
	data->plane[Y] = old_planex * sin(-R_SPEED) + data->plane[Y]
		* cos(-R_SPEED);
	return (1);
}

int	displaymoves(t_data *data)
{
	data->moved += moving(data);
	if (data->moved == 0)
		return (1);
	raycast(data);
	return (0);
}

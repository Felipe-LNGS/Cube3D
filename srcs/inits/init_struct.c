/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/16 11:10:39 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	initiate_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit_free(data, "MLX error");
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_W, SCREEN_H,
			"RubiksCub3D");
	if (!data->win_ptr)
		exit_free(data, "MLX error");
}

void	init_struct(t_data *data)
{
	t_map	*map;
	t_imgs	*img;

	img = ft_calloc(1, sizeof(t_imgs));
	if (!img)
		exit_free(data, MERROR);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_free(data, MERROR);
	ft_bzero(img, sizeof(t_imgs));
	ft_bzero(map, sizeof(t_map));
	ft_bzero(data, sizeof(t_data));
	data->map = map;
	data->img = img;
}

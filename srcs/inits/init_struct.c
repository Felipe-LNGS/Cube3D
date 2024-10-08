/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:47:16 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 15:03:46 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

// creation: mlx_ptr + window
void	initiate_mlx(t_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_W, SCREEN_H,
			"RubiksCub3D");
	if (!data->win_ptr)
		exit_free(data, "Error\nMLX winptr");
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

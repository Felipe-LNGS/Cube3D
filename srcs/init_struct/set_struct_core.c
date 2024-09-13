/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:22:44 by codespace         #+#    #+#             */
/*   Updated: 2024/09/13 13:34:18 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

// void	initiate_mlx(t_data *data)
// {
// 	data->mlx = mlx_init();
// 	// if (data->mlx == NULL)
// 	// 	pre_free_init_struct(data);
// 	// set_img_path_file(data);
// 	mlx_get_screen_size(data->mlx, &(data->sizex), &(data->sizey));
// 	// if (data->width * data->img.width > data->sizex
// 	// 	|| data->height * data->img.height > data->sizey)
// 	// {
// 	// 	ft_printf("Error\nMap too big for sreen!\n");
// 	// 	mlx_destroy_display(data->mlx);
// 	// 	free(data->mlx);
// 	// 	free(data->tab_enemy);
// 	// 	pre_free_init_struct(data);
// 	// }
// 	data->window = NULL;
// 	// set_img(data);
// 	data->window = mlx_new_window(data->mlx, data->map->width * 50,
// data->map->height * 50, "Rubiks3D");
// 	if (data->window == NULL)
// 		free_struct(data);
// 	data->map_x = data->posx_p * 50;
// 	data->map_y = data->posy_p * 50;
// }

void	initiate_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit_free(data, "MLX error");
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_W, SCREEN_H,
			"CUB3D");
	if (!data->win_ptr)
		exit_free(data, "MLX error");
}

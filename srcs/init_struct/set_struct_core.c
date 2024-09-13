/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:22:44 by codespace         #+#    #+#             */
/*   Updated: 2024/09/13 15:38:57 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	initiate_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit_free(data, "MLX error");
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_W, SCREEN_H,
			RED"Rubiks3D"RESET);
	if (!data->win_ptr)
		exit_free(data, "MLX error");
}

void    init_struct(t_data *data)
{
    t_map   map;
    
    ft_bzero(&map, sizeof(t_map));
    ft_bzero(data, sizeof(t_data));
    data->map = &map;
    data->win_ptr = NULL;
    data->posx_p = 0;
    data->posy_p = 0;
}

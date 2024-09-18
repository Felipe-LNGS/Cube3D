/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:39:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 13:55:43 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	free_map(t_data *data)
{
	if (data->map->grid)
		free_split(data->map->grid);
	if (data->map->tmp_grid)
		free_split(data->map->tmp_grid);
	if (data->map->north_path)
		free(data->map->north_path);
	if (data->map->south_path)
		free(data->map->south_path);
	if (data->map->east_path)
		free(data->map->east_path);
	if (data->map->west_path)
		free(data->map->west_path);
	if (data->map->f)
		free(data->map->f);
	if (data->map->c)
		free(data->map->c);
	free(data->map);
}

void	free_all(t_data *data, t_imgs *img)
{
	(void)img;
	free_map(data);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data->img->texture)
		free_split((char **)data->img->texture);
	free(data->img);
}

void	exit_free(t_data *data, char *str)
{
	ft_printf(RED "%s\n" RESET, str);
	free_all(data, data->img);
	exit(1);
}

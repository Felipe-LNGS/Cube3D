/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:39:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/12 14:20:36 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
	{
		free(data->map->f);
	}
	if (data->map->c)
	{
		
		free(data->map->c);
	}
}

void	free_all(t_data *data)
{
	free_map(data);
}

void	exit_free(t_data *data, char *str)
{
	ft_printf(RED "%s\n" RESET, str);
	free_map(data);
	exit(1);
}
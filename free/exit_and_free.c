/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:39:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/12 12:34:03 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void free_map(t_data *data) {
    if (data) {
        // Free the grid if it was allocated
        if (data->map->grid) {
            for (int i = 0; i < data->map->nb_lines; i++) {
                free(data->map->grid[i]); // Free each row
            }
            free(data->map->grid); // Free the array of pointers
        }

        // Free the tmp_grid if it was allocated
        if (data->map->tmp_grid) {
            for (int i = 0; i < data->map->nb_lines; i++) {
                free(data->map->tmp_grid[i]); // Free each row
            }
            free(data->map->tmp_grid); // Free the array of pointers
        }

        // Free the path strings if they were allocated
        free(data->map->north_path);
        free(data->map->south_path);
        free(data->map->east_path);
        free(data->map->west_path);

        // Finally, free the data->map structure itself
        free(data->map);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:33:46 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/10 16:40:21 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	stock_info_bis(char *line, t_data *data)
{
	char	*space_skiped;

	space_skiped = skip_space(line);
	if (!ft_strncmp(line, "F ", 2))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->start_line++;
		data->map->north_path = ft_strdup(space_skiped);
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->start_line++;
		data->map->north_path = ft_strdup(space_skiped);
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->start_line++;
		data->map->north_path = ft_strdup(space_skiped);
	}
}

void	stock_info(char *line, t_data *data)
{
	char	*space_skiped;

	space_skiped = skip_space(line);
	if (!ft_strncmp(line, "NO ", 3))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->start_line++;
		data->map->north_path = ft_strdup(space_skiped);
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->start_line++;
		data->map->north_path = ft_strdup(space_skiped);
	}
	if (!ft_strncmp(line, "WE ", 3))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->start_line++;
		data->map->north_path = ft_strdup(space_skiped);
	}
	stock_info_bis(line, data);
}

int	is_info(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	else if (!ft_strncmp(line, "SO ", 3))
		return (1);
	else if (!ft_strncmp(line, "WE ", 3))
		return (1);
	else if (!ft_strncmp(line, "F ", 2))
		return (1);
	else if (!ft_strncmp(line, "C ", 2))
		return (1);
	else if (!ft_strncmp(line, "EA ", 3))
		return (1);
	else if (line[0] == '\n')
		return (1);
	else
		return (0);
}

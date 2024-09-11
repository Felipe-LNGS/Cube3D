/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:33:46 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/11 18:18:09 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	stock_info_bis(char *line, t_data *data)
{
	char	*space_skiped;

	space_skiped = skip_space(line);
	if (!ft_strncmp(line, "F ", 2))
	{
		space_skiped = skip_space(space_skiped + 2);
		data->map->f = ft_strducube(space_skiped);
		if (!data->map->f)
			exit_free(data, MERROR);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		space_skiped = skip_space(space_skiped + 2);
		data->map->c = ft_strducube(space_skiped);
		if (!data->map->c)
			exit_free(data, MERROR);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->east_path = ft_strducube(space_skiped);
		if (!data->map->east_path)
			exit_free(data, MERROR);
	}
}

void	stock_info(char *line, t_data *data)
{
	char	*space_skiped;

	space_skiped = skip_space(line);
	if (!ft_strncmp(line, "NO ", 3))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->north_path = ft_strducube(space_skiped);
		if (!data->map->north_path)
			exit_free(data, MERROR);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->south_path = ft_strducube(space_skiped);
		if (!data->map->south_path)
			exit_free(data, MERROR);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->west_path = ft_strducube(space_skiped);
		if (!data->map->west_path)
			exit_free(data, MERROR);
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
	else
		return (0);
}
static int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strlen(str) > 3)
			return (1);
		if (!ft_isdigit(str[i]))
			return (1);
		if (ft_atoi(str) > 255)
			return (1);
		i++;
	}
	return (0);
}
void	split_rgb(t_data *data, char *rgb, char who)
{
	char	**splited;
	int		i;

	splited = ft_split(rgb, ',');
	i = 0;
	while (i < 3)
	{
		if (check_value(splited[i]) == 1)
			exit_free(data, "Invalid rgb code");
		if (who =='F')
			data->map->f_tab[i] = ft_atoi(splited[i]);
		if (who =='C')
			data->map->c_tab[i] = ft_atoi(splited[i]);
		i++;
	}
	if (who =='F')
		data->map->c_color = rgb_to_int(data->map->f_tab);
	if (who =='C')
		data->map->f_color = rgb_to_int(data->map->c_tab);
}

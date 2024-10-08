/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:33:46 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 15:01:48 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	stock_info_bis(char *line, t_data *data)
{
	char	*space_skiped;

	space_skiped = skip_space(line);
	if (!ft_strncmp(line, "F ", 2) && !data->map->f)
	{
		space_skiped = skip_space(space_skiped + 2);
		data->map->f = ft_strducube(space_skiped, data);
		if (!data->map->f)
			exit_free(data, MERROR);
	}
	else if (!ft_strncmp(line, "C ", 2) && !data->map->c)
	{
		space_skiped = skip_space(space_skiped + 2);
		data->map->c = ft_strducube(space_skiped, data);
		if (!data->map->c)
			exit_free(data, MERROR);
	}
	else if (!ft_strncmp(line, "EA ", 3) && !data->map->east_path)
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->east_path = ft_strducube(space_skiped, data);
		if (!data->map->east_path)
			exit_free(data, MERROR);
	}
}

void	stock_info(char *line, t_data *data)
{
	char	*space_skiped;

	space_skiped = skip_space(line);
	if (!ft_strncmp(line, "NO ", 3) && !data->map->north_path)
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->north_path = ft_strducube(space_skiped, data);
		if (!data->map->north_path)
			exit_free(data, MERROR);
	}
	else if (!ft_strncmp(line, "SO ", 3) && !data->map->south_path)
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->south_path = ft_strducube(space_skiped, data);
		if (!data->map->south_path)
			exit_free(data, MERROR);
	}
	else if (!ft_strncmp(line, "WE ", 3) && !data->map->west_path)
	{
		space_skiped = skip_space(space_skiped + 3);
		data->map->west_path = ft_strducube(space_skiped, data);
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
	int	digit_count;

	i = 0;
	digit_count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			digit_count++;
		else if (str[i] == '\n')
		{
			i++;
			continue ;
		}
		else
			return (1);
		i++;
	}
	if (ft_atoi(str) > 255)
		return (printf("fsd \n"), 1);
	if (digit_count == 0)
		return (1);
	return (0);
}

void	split_rgb(t_data *data, char *rgb, char who, char **tab)
{
	int	i;

	if (!rgb)
		exit_free(data, "Error\nMissing rgb code");
	tab = ft_split(rgb, ',');
	if (!tab)
		exit_free(data, MERROR);
	i = -1;
	while (++i < 3)
	{
		if (tab[i] && check_value(tab[i]) == 0)
		{
			if (who == 'F' && data->map->f)
				data->map->f_tab[i] = ft_atoi(tab[i]);
			if (who == 'F')
				data->map->f_color = rgb_to_int(data->map->f_tab);
			if (who == 'C' && data->map->c)
				data->map->c_tab[i] = ft_atoi(tab[i]);
			if (who == 'C')
				data->map->c_color = rgb_to_int(data->map->c_tab);
		}
		else
			(free_split(tab), exit_free(data, "Error\nInvalid rgb code"));
	}
	free_split(tab);
}

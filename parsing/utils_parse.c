/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:21:33 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/11 16:55:47 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	free_grid(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map->nb_lines)
	{
		free(data->map->grid[i]);
		i++;
	}
	free(data->map->grid);
}

void	print_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->nb_lines)
	{
		j = 0;
		while (j < data->map->height)
		{
			ft_printf("%c", data->map->tmp_grid[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
}

char	*skip_space(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

char	*ft_strducube(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(ft_strlen(s) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		if (s[i] != '\n')
			dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
// verifier autour de chaque 0 si il y a autre chose que un 1 c'est carton rouge
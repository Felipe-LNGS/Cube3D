/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:21:33 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 12:25:22 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

int	open_file(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, __O_DIRECTORY);
	if (fd > 0)
	{
		return (close(fd), exit_free(data, "Error\nTry to read empty map."), 1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (close(fd), exit_free(data, "Error\nFailed to open file."), 1);
	return (fd);
}

char	*skip_space(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

char	*ft_strducube(char *s, t_data *data)
{
	char	*dest;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (s[len] != '\0')
	{
		if (s[len] != '\n')
			len++;
		else
			len++;
	}
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (exit_free(data, MERROR), NULL);
	while (s[i] != '\0' && s[i] != '\n')
	{
		dest[j] = s[i];
		j++;
		i++;
	}
	return (dest[j] = '\0', dest);
}

// Verifie le format du fichier qui essaye d'etre ouvert
int	check_format(char *map)
{
	int	len;

	len = ft_strlen(map);
	if (map[len - 4] == '.' && map[len - 3] == 'c' && map[len - 2] == 'u'
		&& map[len - 1] == 'b' && map[len] == '\0')
		return (0);
	else
		return (1);
}

int	rgb_to_int(int *rgb)
{
	int	color;

	color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	return (color);
}
